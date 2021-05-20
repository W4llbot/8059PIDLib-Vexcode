#ifndef _8059_SIMPLE_PID_CONTROL_HPP_
#define _8059_SIMPLE_PID_CONTROL_HPP_
extern double errorEncdL, errorEncdR, targPowerL, targPowerR, powerL, powerR, errorBearing;
extern bool pauseBase;

void baseMove(double dis, double kp, double ki, double kd);
void baseMove(double dis);
void baseMove(double x, double y, double p, double i, double d);
void baseMove(double x, double y);

void baseTurn(double a, double kp, double ki, double kd);
void baseTurn(double a);
void baseTurnRelative(double a, double p, double i, double d);
void baseTurnRelative(double a);
void baseTurn(double x, double y, double p, double i, double d, bool inverted);
void baseTurn(double x, double y, bool inverted);

void powerBase(double l, double r);
void timerBase(double l, double r, double t);
void unPauseBase();
void waitBase(double cutoff);
void waitBaseNoD(double cutoff);
int Control();
void resetCoords(double x, double y, double a);
#endif