#include "vex.h"
const double inPerDeg = 0.0461916735714906;
double X = 0, Y = 0, prevEncdL = 0, prevEncdR = 0;
void setCoords(double x, double y){
  X = x;
  Y = y;
}
int Odometry(){
  while(true){
    if(Imu.isCalibrating()){
      resetCoords(0, 0);
    }else {
      double encdChangeL = encdL-prevEncdL;
      double encdChangeR = encdR-prevEncdR;

      double distance = (encdChangeL + encdChangeR)/2*inPerDeg;
      X += distance*cos(angle);
      Y += distance*sin(angle);
      /** update prev variables */
      prevEncdL = encdL;
      prevEncdR = encdR;
    }
    wait(5, msec);
  }
  return 0;
}
void resetPrevEncd() {
  prevEncdL = 0;
  prevEncdR = 0;
}
