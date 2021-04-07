#include "vex.h"

double encdL = 0, encdR = 0, bearing = 0, angle = halfPI;

int Sensors() {
  while(true){
    if(!Imu.isCalibrating()) {
      encdL = BL.rotation(deg);
      encdR = BR.rotation(deg);
      bearing = Imu.rotation();
      angle = halfPI - bearing * toRad;
    }
    wait(20, msec);
  }
  return 0;
}