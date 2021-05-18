#include "vex.h"
#include "auton-sets.h"

void shootPreload() {
  defaultShootSpeed = 50;
  shootBall();
  wait(300, msec);
  shootTrigger = false;
  defaultShootSpeed = 100;
  printf("completed");
}

// double offset = 0;


// #define DEFAULT_KP 0.23
// #define DEFAULT_KI 0
// #define DEFAULT_KD 10
// #define DEFAULT_TURN_KP 0.32
// #define DEFAULT_TURN_KI 0
// #define DEFAULT_TURN_KD 10
void red10() {
  resetCoords(0, 0, -58.3);
  shootPreload();
  baseMove(33);
  waitBase(2000);
  baseTurn(-27, 60, 0.3, 0, 10, false);
  waitBase(2000);
  intake(100);
  baseMove(31);
  waitBase(2000);
  baseTurn(-94, 0.34, 0, 10);
  waitBase(2000);
  intake(-5);
  baseMove(-23);
  waitBase(2000);
  // baseMove(10);
  // waitBase(1000);
  baseTurn(-49, 0 , 0.3, 0, 10, false);
  waitBase(2000);
  // wait(500, msec);
  // resetPrevEncd();
  // intake(0);
  resetPrevEncd();
  baseMove(62);
  waitBase(3000);
  intake(0);
  baseMove(-40);
  intake(-50);
  waitBase(3000);
  baseTurn(69, -2, 0.33, 0, 10, false);
  waitBase(2000);
  // wait(500, msec);
  // resetPrevEncd();
  intake(-5);
  baseMove(98);
  waitBase(3000);
  baseMove(20);
  wait(100, msec);
  shootBall();
  wait(200, msec);
  forceOuttake(true);
  intake(-20);
}

void blue10() {
//   resetCoords(0, 0);
//   offset = 59.5;
//   shootPreload();

//   // Intake red ball
//   baseMove(27, 0.27, 0);
//   waitBase(1500);
//   // delay(200);
//   baseTurn(0 + offset, 1.45, 0);
//   waitBase(1000);
//   intake(127);
//   baseMove(34, 0.27, 0);
//   waitBase(2000);
//   wait(100, msec);

//   // Turn and ram ball
//   baseTurn(-94 + offset, 1.25, 0);
//   waitBase(1500);
//   baseMove(-21, 0.33, 0);
//   waitBase(2000);
//   wait(300, msec);

//   // turn and score goal 2
//   baseTurn(-134 + offset, 1.81, 0);
//   waitBase(1000);
//   baseMove(62, 0.25, 0);
//   intake(127);
//   waitBase(2500);
//   wait(200, msec);
//   shootBall();
//   wait(10, msec);
//   intake(0);
//   waitShooter();

//   baseMove(-57, 0.25, 0);
//   waitBase(2500);
//   baseTurn(-236 + offset, 1.22, 0);
//   waitBase(2000);
//   baseMove(84, 0.25, 0);
//   intake(127);
//   waitBase(3000);
//   intake(0);
//   shootBall();
//   wait(500, msec);
//   intake(-127);
//   forceOuttake(true);
//   wait(500, msec);
//   forceOuttake(false);
}
