#include "vex.h"
const double inPerDeg = 0.0243666691788904;
const double baseWidth = 9.986975605244217;
double X = 0, Y = 0, prevEncdL = 0, prevEncdR = 0, prevAngle = 0;
double angle = 0, lastResetAngle = 0;
void setCoords(double x, double y, double angle){
  X = x;
  Y = y;
}
int Odometry(){
  while(true){
    double encdChangeL = (encdL-prevEncdL)*inPerDeg;
    double encdChangeR = (encdR-prevEncdR)*inPerDeg;
    angle = lastResetAngle + (encdL - encdR)*inPerDeg/baseWidth; //Theta = (s2-s1)/width
    double deltaAngle = angle - prevAngle;
    double sumEncdChange = encdChangeL + encdChangeR;

    if(deltaAngle == 0) //Cannot divide by 0
    {
			X += sumEncdChange/2*sin(angle);            	//Simple trigo
			Y += sumEncdChange/2*cos(angle);
		}
		else                //Refer to formulas
		{
			double halfDeltaAngle = deltaAngle/2;
			double strDist = (sumEncdChange/deltaAngle)*sin(halfDeltaAngle);
			X += strDist * sin(prevAngle+halfDeltaAngle);
			Y += strDist * cos(prevAngle+halfDeltaAngle);
		}
    /** update prev variables */
    prevEncdL = encdL;
    prevEncdR = encdR;
    prevAngle = angle;
  wait(5, msec);
  }
  return 0;
}
void resetPrevEncd() {
  prevEncdL = 0;
  prevEncdR = 0;
}
