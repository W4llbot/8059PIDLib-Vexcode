#ifndef _MECH_LIB_H_
#define _MECH_LIB_H_

extern double defaultShootSpeed;
extern bool shootTrigger, autoIndex;
int indexerControl();

int shooterControl();
void shootBall();
void forceOuttake(bool value);
void waitShooter();
void intake(double speed);
void waitLoaded();

#endif