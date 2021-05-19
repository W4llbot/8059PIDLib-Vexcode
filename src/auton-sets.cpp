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
  double start = Timer.time();
  resetCoords(0, 0, -58.3);
  shootPreload();
  baseMove(32);
  waitBase(2000);
  // baseTurn(-27, 60, 0.3, 0, 10, false);
  baseTurn(2, 0.305, 0, 10);
  waitBase(2000);
  intake(100);
  baseMove(33);
  waitBase(2000);
  baseTurn(-94, 0.33, 0, 10);
  waitBase(2000);
  intake(0);
  baseMove(-23.5);
  waitBase(2000);
  // baseMove(10);
  // waitBase(1000);
  // baseTurn(-49, 0 , 0.29, 0, 10, false);
  baseTurn(-138, 0.3, 0, 10);
  waitBase(2000);
  // wait(500, msec);
  // resetPrevEncd();
  // intake(0);
  resetPrevEncd();
  baseMove(62.5);
  waitBase(3000);
  intake(0);
  baseMove(-40);
  intake(-30);
  waitBase(3000);
  // baseTurn(69, -2, 0.33, 0, 10, false);
  baseTurn(-250.5, 0.33, 0, 10);
  waitBase(1500);
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
  wait(200, msec);
  printf("Time: %.2f", Timer.time() - start);
}

void blue10() {
  double start = Timer.time();
  resetCoords(0, 0, -58.3);
  shootPreload();
  baseMove(29);
  waitBase(2000);
  // baseTurn(-27, 60, 0.3, 0, 10, false);
  baseTurn(2, 0.305, 0, 10);
  waitBase(1500);
  intake(100);
  baseMove(32.5);
  waitBase(2000);
  baseTurn(-95, 0.32, 0, 10);
  waitBase(2000);
  intake(0);
  baseMove(-23.7);
  waitBase(1000);
  // baseMove(10);
  // waitBase(1000);
  // baseTurn(-49, 0 , 0.29, 0, 10, false);
  baseTurn(-135, 0.3, 0, 10);
  waitBase(2000);
  // wait(500, msec);
  // resetPrevEncd();
  // intake(0);
  resetPrevEncd();
  baseMove(64.5);
  waitBase(3000);
  intake(0);
  baseMove(-40);
  intake(-50);
  waitBase(3000);
  // baseTurn(69, -2, 0.33, 0, 10, false);
  baseTurn(-247.5, 0.32, 0, 10);
  waitBase(1500);
  // wait(500, msec);
  // resetPrevEncd();
  intake(-5);
  baseMove(98);
  waitBase(3000);
  baseMove(20);
  // wait(100, msec);
  shootBall();
  wait(100, msec);
  forceOuttake(true);
  intake(-20);
  wait(200, msec);
  printf("Time: %.2f", Timer.time() - start);
}
