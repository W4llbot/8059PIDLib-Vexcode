#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor FL = motor(PORT5, ratio18_1, false);
motor BL = motor(PORT3, ratio18_1, false);
motor FR = motor(PORT4, ratio18_1, true);
motor BR = motor(PORT10, ratio18_1, true);
// inertial Imu = inertial(PORT17);
motor LRoller = motor(PORT8, ratio6_1, false);
motor RRoller = motor(PORT7, ratio6_1, true);
motor Shooter = motor(PORT21, ratio6_1, false);
motor Indexer = motor(PORT1, ratio6_1, true);
line ShooterLine = line(Brain.ThreeWirePort.E);
line IndexerLine = line(Brain.ThreeWirePort.F);
encoder LEncoder = encoder(Brain.ThreeWirePort.G);
encoder REncoder = encoder(Brain.ThreeWirePort.C);
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
  // Imu.calibrate();
  // Brain.Screen.print("Calibrating Gyro for Drivetrain");
  // // wait for the gyro calibration process to finish
  // while (Imu.isCalibrating()) {
  //   wait(25, msec);
  // }
  // reset the screen now that the calibration is complete
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  wait(50, msec);
  Brain.Screen.clearScreen();
}