/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    12, 2, 11, 1, 5 
// LRoller              motor         18              
// RRoller              motor         20              
// Shooter              motor         9               
// Router               motor         10              
// ShooterLine          line          F               
// RouterLine           line          G               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  pauseBase = false;
  baseMove(30, 0.27, 0);
  waitBase(2000);
  baseTurn(90, 1.2, 0);
  waitBase(2000);

  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
bool tankDrive = true;
void toggleDriveMode() {
  // if(tankDrive) tankDrive = false;
  // else tankDrive = true;
  printf("toggle\n");
  tankDrive = false;
}

void usercontrol(void) {
  pauseBase = true;
  // User control code here, inside the loop
  double deadBand = 5;
  double leftSpeed, rightSpeed;
  
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.
    Controller1.ButtonY.pressed(toggleDriveMode);
    printf("tank drive: %.2f\n", FL.velocity(pct));

    if(tankDrive) {
      leftSpeed = Controller1.Axis3.value();
      rightSpeed = Controller1.Axis2.value();
    }else {
      double power = Controller1.Axis3.value();
      double turn = Controller1.Axis1.value();

      leftSpeed = power + turn;
      rightSpeed = power - turn;
    }

    if(fabs(leftSpeed) < deadBand) {
      FL.stop(brake);
      BL.stop(brake);
    }else {
      FL.spin(fwd, leftSpeed, pct);
      BL.spin(fwd, leftSpeed, pct);
    }

    if(fabs(rightSpeed) < deadBand) {
      FR.stop(brake);
      BR.stop(brake);
    }else {
      FR.spin(fwd, rightSpeed, pct);
      BR.spin(fwd, rightSpeed, pct);
    }
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  task controlTask(Control);
  task sensorTask(Sensors);
  task odomTask(Odometry);
  task debugTask(Debug);
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
