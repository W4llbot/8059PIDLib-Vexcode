#include "vex.h"
#define DEFAULT_KP 0.23
#define DEFAULT_KI 0
#define DEFAULT_KD 10
#define DEFAULT_TURN_KP 0.32
#define DEFAULT_TURN_KI 0
#define DEFAULT_TURN_KD 10
#define KI_LIMIT 0
#define RAMPING_POW 2
#define DISTANCE_LEEWAY 8
#define MAX_POW 100

double targEncdL = 0, targEncdR = 0;
double errorEncdL = 0, errorEncdR = 0;
double powerL = 0, powerR = 0;
double targPowerL = 0, targPowerR = 0;
double kP = DEFAULT_KP, kD = DEFAULT_KD, kI = DEFAULT_KI;

bool turnMode = false, pauseBase = false;

void baseMove(double dis, double kp, double ki, double kd){\
  targEncdL = encdL;
  targEncdR = encdR;
  // resetPrevEncd();
  printf("baseMove(%.2f)\n", dis);
  targEncdL += dis/inPerDeg;
  targEncdR += dis/inPerDeg;

  kP = kp;
  kI = ki;
  kD = kd;
}
void baseMove(double dis){
  baseMove(dis, DEFAULT_KP, DEFAULT_KI, DEFAULT_KD);
}

void baseMove(double x, double y, double p, double i, double d){
  printf("baseMove(%.2f, %.2f)\n", x, y);
	double errY = y-Y;
	double errX = x-X;
	double distance = sqrt(errY*errY + errX*errX);
	double targAngle = atan2(errX,errY);
	// printf("Angle: %f %f", targAngle, position.angle);
	// printf("Distance: %f",distance);

	int negator = 1;
  if(fabs(targAngle-angle) >= PI/2) negator = -1;

  targEncdL += distance/inPerDeg*negator;
  targEncdR += distance/inPerDeg*negator;

  kP = p;
  kI = i;
  kD = d;
}

void baseMove(double x, double y){
  baseMove(x, y, DEFAULT_KP, DEFAULT_KI, DEFAULT_KD);
}


void baseTurn(double a, double kp, double ki, double kd){
  wait(100, msec);
  printf("baseTurn(%.2f, %.2f, %.2f)\n", a, kp, kd);
  double error = a*toRad - angle;
  double diff = error*baseWidth/inPerDeg/2;

  targEncdL += diff;
  targEncdR += -diff;
	kP = kp;
  kI = ki;
	kD = kd;
}

void baseTurn(double a){
  baseTurn(a, DEFAULT_TURN_KP, DEFAULT_TURN_KI, DEFAULT_TURN_KD);
}

void baseTurnRelative(double a, double p, double i, double d){

  double diff = a*toRad*baseWidth/inPerDeg/2;
  targEncdL += diff;
  targEncdR += -diff;

  kP = p;
  kI = i;
  kD = d;
}

void baseTurnRelative(double a){
  baseTurnRelative(a, DEFAULT_TURN_KP, DEFAULT_TURN_KI, DEFAULT_KD);
}

void baseTurn(double x, double y, double p, double i, double d, bool inverted){
  printf("deltas: %.2f, %.2f\n", x, X);
	double targAngle = atan2((x-X), (y-Y));
  printf("Turn to angle: %.2f\n", targAngle * toDeg);
	if(inverted) targAngle -= halfPI;
  // double diff = (targAngle - angle + lastResetAngle)*baseWidth/inPerDeg/2;
  // targEncdL += diff;
  // targEncdR += -diff;
  // kP = p;
  // kD = d;
  double diffAngle = boundRad(targAngle-angle);
  if(diffAngle > PI) diffAngle -= twoPI;
  targAngle = angle + diffAngle;
  printf("diffANgle: %.1f\n", diffAngle*toDeg);
  baseTurn(targAngle*toDeg, p, i, d);
}

void baseTurn(double x, double y, bool inverted){
  baseTurn(x,y,DEFAULT_TURN_KP,DEFAULT_TURN_KI,DEFAULT_TURN_KD,inverted);
}

void powerBase(double l, double r) {
  printf("powerBase(%.2f, %.2f)\n", l, r);
  pauseBase = true;
  powerL = l;
  powerR = r;
}

void timerBase(double l, double r, double t) {
  printf("timerBase(%.2f, %.2f, %.2f)\n", l, r, t);
  pauseBase = true;
  powerL = l;
  powerR = r;
  wait(t, msec);
  powerL = 0;
  powerR = 0;
  pauseBase = false;
  resetCoords(X, Y, angle);
}

void unPauseBase() {
  powerL = 0;
  powerR = 0;
  pauseBase = false;
  resetCoords(X, Y, angle);
}

void waitBase(double cutoff){
	double start = Timer.time();
  while((fabs(targEncdL - encdL) > DISTANCE_LEEWAY || fabs(targEncdR - encdR) > DISTANCE_LEEWAY) && (Timer.time()-start) < cutoff) wait(20, msec);
  printf("Time taken %.2f\n", (Timer.time() - start));
  wait(100, msec);
  // targEncdL = encdL;
  // targEncdR = encdR;
  resetPrevEncd();
}

int Control(){
  int dT = 5;
  double prevErrorEncdL = 0, prevErrorEncdR = 0, integralL = 0, integralR = 0;
  while(true){
    if(!pauseBase) {
      errorEncdL = targEncdL - encdL;
      errorEncdR = targEncdR - encdR;
      // printf("\n");
      // printf("errorEncd: %.1f\t%.1f\n", errorEncdL, errorEncdR);
      double deltaErrorEncdL = errorEncdL - prevErrorEncdL;
      double deltaErrorEncdR = errorEncdR - prevErrorEncdR;
      // printf("prevErrorEncd: %.1f\t%.1f\n", prevErrorEncdL, prevErrorEncdR);
      // printf("deltaErrorEncd: %.1f\t%.1f\n", deltaErrorEncdL, deltaErrorEncdR);
      double pd_targPowerL = errorEncdL * kP + deltaErrorEncdL * kD;
      double pd_targPowerR = errorEncdR * kP + deltaErrorEncdR * kD;
      // printf("pd: %.2f\t%.2f\n", pd_targPowerL, pd_targPowerR);
      double pd_maxTargPower = std::max(fabs(pd_targPowerL), fabs(pd_targPowerR));
      double setPower = min(pd_maxTargPower, MAX_POW);
      // printf("setPower: %.2f\n", setPower);
      double lToR = ((pd_targPowerR != 0)? (pd_targPowerL/pd_targPowerR) : 1);
      if(lToR != 0){
          if(fabs(lToR)>=1){
            targPowerL = setPower*sign(pd_targPowerL);
            targPowerR = setPower*sign(pd_targPowerR)/fabs(lToR);
          } else{
            targPowerL = setPower*sign(pd_targPowerL)*fabs(lToR);
            targPowerR = setPower*sign(pd_targPowerR);
        }
      }
      // printf("targPower: %.2f\t%.2f\n", targPowerL, targPowerR);
      double deltaPowerL = targPowerL - powerL;
      double deltaPowerR = targPowerR - powerR;
      // printf("power: %.1f\t%.1f\n", powerL, powerR);
      // printf("delta: %.1f\t%.1f\n", deltaPowerL, deltaPowerR);
      deltaPowerL = abscap(deltaPowerL, RAMPING_POW);
      deltaPowerR = abscap(deltaPowerR, RAMPING_POW);
      // printf("capped delta: %.1f\t%.1f\n", deltaPowerL, deltaPowerR);
      powerL += deltaPowerL;
      powerR += deltaPowerR;
      // printf("updated power: %.1f\t%.1f\n", powerL, powerR);
      // manual base compensation factor
      double mod = 0.999; //>1 to make left faster, <1 to make right faster
      if(mod >= 1) powerR /= mod;
      else powerL *= mod;
      prevErrorEncdL = errorEncdL;
      prevErrorEncdR = errorEncdR;
      FL.spin(fwd, powerL, pct);
      BL.spin(fwd, powerL, pct);
      FR.spin(fwd, powerR, pct);
      BR.spin(fwd, powerR, pct);
    }
    wait(dT, msec);
  }

  return 0;
}

void resetCoords(double x, double y, double angleInDeg){
  FL.resetRotation();
  FR.resetRotation();
  BL.resetRotation();
  BR.resetRotation();

  LEncoder.resetRotation();
  REncoder.resetRotation();
  resetPrevEncd();

  targEncdL = 0;
  targEncdR = 0;

  setCoords(x, y, angleInDeg);
}