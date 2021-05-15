#include "vex.h"

double encdL = 0, encdR = 0;

int Sensors() {
  while(true){
    encdL = -LEncoder.value();
    encdR = REncoder.value();
    wait(5, msec);
  }
  return 0;
}