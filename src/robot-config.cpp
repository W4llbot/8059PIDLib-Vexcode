#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor FL = motor(PORT12, ratio18_1, true);
motor BL = motor(PORT2, ratio18_1, true);
motor FR = motor(PORT11, ratio18_1, false);
motor BR = motor(PORT1, ratio18_1, false);
inertial Imu = inertial(PORT5);
motor LRoller = motor(PORT18, ratio18_1, false);
motor RRoller = motor(PORT20, ratio18_1, false);
motor Shooter = motor(PORT9, ratio18_1, false);
motor Router = motor(PORT10, ratio18_1, false);
line ShooterLine = line(Brain.ThreeWirePort.F);
line RouterLine = line(Brain.ThreeWirePort.G);
timer Timer;

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  Brain.Screen.print("Device initialization...");
  Brain.Screen.setCursor(2, 1);
  // calibrate the drivetrain gyro
  wait(200, msec);
  Imu.calibrate();
  Brain.Screen.print("Calibrating Gyro for Drivetrain");
  // wait for the gyro calibration process to finish
  while (Imu.isCalibrating()) {
    wait(25, msec);
  }
  // reset the screen now that the calibration is complete
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  wait(50, msec);
  Brain.Screen.clearScreen();
}