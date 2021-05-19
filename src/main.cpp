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
  // resetCoords(0, 0, 0);
  double start = Timer.time();
  pauseBase = false;
  // baseMove(30, 0.21, 0, 10);
  // baseTurn(111, 0.32, 0, 10);
  // wait(100000000, msec);
  red10();
  // blue10();
  // printf("atan: %.2f\n", atan2(-10, -5) * toDeg);
  double final = Timer.time() - start;
  Controller1.Screen.setCursor(1, 0);
  printf("Run time: %.2f", final);
  while(true) Controller1.Screen.print("Time: %.2f\n", final);

  // ..........................................................................
  
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
bool tankDrive = true, tankDriveToggle = true;
void toggleDriveMode() {
  // if(tankDrive) tankDrive = false;
  // else tankDrive = true;
  if(tankDriveToggle) {
    tankDrive = !tankDrive;
    tankDriveToggle = false;
  }
  wait(200, msec);
  tankDriveToggle = true;
}

bool autoIndexToggle = true;
void toggleAutoIndex() {
  if(autoIndexToggle) {
    autoIndex = !autoIndex;
    autoIndexToggle = false;
  }
  wait(200, msec);
  autoIndexToggle = true;
}

void usercontrol(void) {
  pauseBase = true;
  // User control code here, inside the loop
  double deadBand = 5;
  double leftSpeed, rightSpeed;
  // bool forceZero = false;
  
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.
    // Controller1.ButtonB.pressed(toggleAutoIndex);

    // if(autoIndex) {
      shootReverse = Controller1.ButtonR2.pressing();
      if(Controller1.ButtonR1.pressing()) shootBall();
      forceOuttake(Controller1.ButtonL2.pressing());
      if(Controller1.ButtonX.pressing()) {
        shootBall();
        defaultShootSpeed = 20;
        autoIndex = false;
      }else {
        defaultShootSpeed = 100;
        autoIndex = true;
      }
    // }else {
    //   double cycleDir = (Controller1.ButtonR1.pressing() - Controller1.ButtonR2.pressing());
    //   Indexer.spin(fwd, cycleDir*100, pct);
    //   Shooter.spin(fwd, cycleDir*100, pct);
    // }
    intake((Controller1.ButtonL1.pressing() - Controller1.ButtonL2.pressing()) * defaultShootSpeed);

    Controller1.ButtonY.pressed(toggleDriveMode);

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
      FL.stop(coast);
      BL.stop(coast);
    }else {
      FL.spin(fwd, leftSpeed, pct);
      BL.spin(fwd, leftSpeed, pct);
    }

    if(fabs(rightSpeed) < deadBand) {
      FR.stop(coast);
      BR.stop(coast);
    }else {
      FR.spin(fwd, rightSpeed, pct);
      BR.spin(fwd, rightSpeed, pct);
    }
    wait(5, msec); // Sleep the task for a short amount of time to
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
  task shooterControlTask(shooterControl);
  task indexerControlTask(indexerControl);
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
