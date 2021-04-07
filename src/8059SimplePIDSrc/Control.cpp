#include "vex.h"
#define DEFAULT_KP 0.25
/*  10 = 0.35,
    15 = 0.3,
    20-30-35 = 0.27,
    40-50-60 = 0.25 */
#define DEFAULT_KD 0.0
#define DEFAULT_TURN_KP 1.35
/*  20 = 2.5,
    30 = 2.1,
    40 = 1.8,
    50 = 1.6,
    60 = 1.5,
    70 = 1.4,
    80 = 1.35,
    90 = 1.3,
    100 = 1.25,
    110 = 1.2,
    120 = 1.15,
    130 = 1.13,
    140 = 1.11,
    150 = 1.08,
    160 = 1.05,
    170 = 1.02,
    175 = 0.98,
    180 = 0.967 */
#define DEFAULT_TURN_KD 0.0
#define RAMPING_POW 1.2
#define DISTANCE_LEEWAY 15
#define BEARING_LEEWAY 1.5
#define MAX_POW 120

double targEncdL = 0, targEncdR = 0, targBearing = 0;
double errorEncdL = 0, errorEncdR = 0, errorBearing = 0;
double powerL = 0, powerR = 0;
double targPowerL = 0, targPowerR = 0;
double kP = DEFAULT_KP, kD = DEFAULT_KD;

bool turnMode = false, pauseBase = false;

void baseMove(double dis, double kp, double kd){
  printf("baseMove(%.2f)\n", dis);
  turnMode = false;
  targEncdL += dis/inPerDeg;
  targEncdR += dis/inPerDeg;

  kP = kp;
  kD = kd;
}
void baseMove(double dis){
  baseMove(dis, DEFAULT_KP, DEFAULT_KD);
}

void baseTurn(double p_bearing, double kp, double kd){
  printf("baseTurn(%.2f, %.2f, %.2f)\n", p_bearing, kp, kd);
  turnMode = true;
  targBearing = p_bearing;
	kP = kp;
	kD = kd;
}
void baseTurn(double bearing){
  baseTurn(bearing, DEFAULT_TURN_KP, DEFAULT_TURN_KD);
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
  if(turnMode) {
    while(fabs(targBearing - bearing) > BEARING_LEEWAY && (Timer.time()-start) < cutoff) wait(20, msec);
  }else{
    while((fabs(targEncdL - encdL) > DISTANCE_LEEWAY || fabs(targEncdR - encdR) > DISTANCE_LEEWAY) && (Timer.time()-start) < cutoff) wait(20, msec);
  }

  targEncdL = encdL;
  targEncdR = encdR;
  printf("Tima taken %.2f\n", (Timer.time() - start));
}

int Control(){
  double prevErrorEncdL = 0, prevErrorEncdR = 0, prevErrorBearing = 0;
  while(true){
    if(!Imu.isCalibrating() && !pauseBase) {
      if(turnMode){
        errorBearing = targBearing - bearing;
        double deltaErrorBearing = errorBearing - prevErrorBearing;

        targPowerL = errorBearing * kP + deltaErrorBearing * kD;
        targPowerR = -targPowerL;

        prevErrorBearing = errorBearing;
      }else{
        errorEncdL = targEncdL - encdL;
        errorEncdR = targEncdR - encdR;

        double deltaErrorEncdL = errorEncdL - prevErrorEncdL;
        double deltaErrorEncdR = errorEncdR - prevErrorEncdR;

        targPowerL = errorEncdL * kP + deltaErrorEncdL * kD;
        targPowerR = errorEncdR * kP + deltaErrorEncdR * kD;

        prevErrorEncdL = errorEncdL;
        prevErrorEncdR = errorEncdR;
      }

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
    wait(5, msec);
  }

  return 0;
}

void resetCoords(double x, double y){
  FL.resetRotation();
  FR.resetRotation();
  BL.resetRotation();
  BR.resetRotation();
  resetPrevEncd();

  targBearing = bearing;
  targEncdL = 0;
  targEncdR = 0;

  setCoords(x, y);
}