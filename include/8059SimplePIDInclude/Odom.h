#ifndef _8059_SIMPLE_PID_ODOM_HPP_
#define _8059_SIMPLE_PID_ODOM_HPP_
extern double X, Y, angle;
extern const double inPerDeg, baseWidth;
void setCoords(double x, double y, double angle);
int Odometry();
void resetPrevEncd();
#endif