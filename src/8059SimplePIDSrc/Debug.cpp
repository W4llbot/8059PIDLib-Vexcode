#include "vex.h"
int DEBUG_MODE = 2;
void printPosMaster(){
  Controller1.Screen.setCursor(3, 0);
  // if(Imu.isCalibrating()) Controller1.Screen.print("Callibrate IMU");
  Controller1.Screen.print("%.2f %.2f %.2f", X, Y, angle * toDeg);
}
void printPosTerminal(){
  printf("x: %.2f y: %.2f bearing: %.2f\n", X, Y, angle * toDeg);
}
void printEncdTerminal(){
  printf("encdL: %.2f encdR: %.2f\n", encdL, encdR);
}
void printErrorTerminal(){
  if(turnMode) printf("errorBearing: %.2f\n", errorBearing);
  else printf("errorEncdL: %.2f errorEncdR: %.2f\n", errorEncdL, errorEncdR);
}
void printTargPowerTerminal(){
  printf("targPowerL: %.2f, targPowerR: %.2f\n", targPowerL, targPowerR);
}
void printPowerTerminal(){
  printf("powerL: %.2f powerR: %.2f\n", powerL, powerR);
}
int Debug(){
  while(true){
    printPosMaster();
    // if(Imu.isCalibrating()) {
    //   printf("imu is calibrating...\n");
    // }else {
      switch(DEBUG_MODE){
        case 1: printPosTerminal(); break;
        case 2: printEncdTerminal(); break;
        case 3: printErrorTerminal(); break;
        case 4: printTargPowerTerminal(); break;
        case 5: printPowerTerminal(); break;
      }
    // }
    wait(50, msec);
  }

  return 0;
}
