#include "vex.h"
#define DEFAULT_KP 0.15
#define DEFAULT_KD 0
#define DEFAULT_KI 0
#define DEFAULT_TURN_KP 1
#define DEFAULT_TURN_KI 0
#define DEFAULT_TURN_KD 30
#define RAMPING_POW 1
#define DISTANCE_LEEWAY 15
#define BEARING_LEEWAY 1.5
#define MAX_POW 100

double targEncdL = 0, targEncdR = 0, targBearing = 0;
double errorEncdL = 0, errorEncdR = 0, errorBearing = 0;
double powerL = 0, powerR = 0;
double targPowerL = 0, targPowerR = 0;
double kP = DEFAULT_KP, kD = DEFAULT_KD, kI = DEFAULT_KI;

bool turnMode = false, pauseBase = false;

void baseMove(double dis, double kp, double ki, double kd){
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
  kD = d;
}

void baseMove(double x, double y){
	baseMove(x,y,0.17,0.15);
}


void baseTurn(double p_bearing, double kp, double ki, double kd){
  printf("baseTurn(%.2f, %.2f, %.2f)\n", p_bearing, kp, kd);
  turnMode = true;
  targBearing = p_bearing;
	kP = kp;
  kI = ki;
	kD = kd;
}
void baseTurn(double bearing){
  baseTurn(bearing, DEFAULT_TURN_KP, DEFAULT_TURN_KI, DEFAULT_TURN_KD);
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
  resetCoords(X, Y);
}

void unPauseBase() {
  powerL = 0;
  powerR = 0;
  pauseBase = false;
  resetCoords(X, Y);
}

void waitBase(double cutoff){
	double start = Timer.time();
  while((fabs(targEncdL - encdL) > DISTANCE_LEEWAY || fabs(targEncdR - encdR) > DISTANCE_LEEWAY) && (Timer.time()-start) < cutoff) wait(20, msec);

  targEncdL = encdL;
  targEncdR = encdR;
  resetPrevEncd();
  printf("Time taken %.2f\n", (Timer.time() - start));
}

int Control(){
  int dT = 5;
  double prevErrorEncdL = 0, prevErrorEncdR = 0, integralL = 0, integralR = 0;
  while(true){
    if(!pauseBase) {
      errorEncdL = targEncdL - encdL;
      errorEncdR = targEncdR - encdR;

      integralL += errorEncdL * dT;
      integralR += errorEncdR * dT;

      double deltaErrorEncdL = (errorEncdL - prevErrorEncdL)/dT;
      double deltaErrorEncdR = (errorEncdR - prevErrorEncdR)/dT;

      targPowerL = errorEncdL * kP + integralL * kI + deltaErrorEncdL * kD;
      targPowerR = errorEncdR * kP + integralR * kI + deltaErrorEncdR * kD;

      prevErrorEncdL = errorEncdL;
      prevErrorEncdR = errorEncdR;

      double deltaPowerL = targPowerL - powerL;
      powerL += abscap(deltaPowerL, RAMPING_POW);
      double deltaPowerR = targPowerR - powerR;
      powerR += abscap(deltaPowerR, RAMPING_POW);

      powerL = abscap(powerL, MAX_POW);
      powerR = abscap(powerR, MAX_POW);

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

  targBearing = angleInDeg * toRad;
  targEncdL = 0;
  targEncdR = 0;

  setCoords(x, y, angle);
}