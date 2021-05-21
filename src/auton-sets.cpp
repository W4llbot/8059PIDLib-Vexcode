#include "vex.h"
#include "auton-sets.h"

void shootPreload() {
  defaultShootSpeed = 50;
  shootBall();
  wait(500, msec);
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
void blue10() {
  double start = Timer.time();
  resetCoords(0, 0, -58.3);
  shootPreload();
  baseMove(32);
  waitBase(1500);
  // baseTurn(-27, 60, 0.3, 0, 10, false);
  baseTurn(1, 0.295, 0, 10);
  waitBase(2000);
  intake(100);
  baseMove(32);
  waitBase(2000);
  baseTurn(-92, 0.29, 0, 10);
  waitBase(2000);
  intake(-10);
  baseMove(-23.5);
  waitBase(1200);
  // baseMove(10);
  // waitBase(1000);
  // baseTurn(-49, 0 , 0.29, 0, 10, false);
  baseTurn(-136, 0.285, 0, 10);
  waitBase(1500);
  // wait(500, msec);
  // resetPrevEncd();
  // intake(0);
  resetPrevEncd();
  baseMove(62.5, 0.14, 0, 5);
  waitBase(2000);
  intake(0);
  baseMove(-40, 0.14, 0, 5);
  intake(-30);
  waitBase(1500);
  // baseTurn(69, -2, 0.33, 0, 10, false);
  baseTurn(-246, 0.285, 0, 10);
  waitBase(1500);
  // wait(500, msec);
  // resetPrevEncd();
  intake(-5);
  baseMove(98, 0.15, 0, 10);
  waitBaseNoD(2500);
  baseMove(20);
  shootBall();
  wait(50, msec);
  forceOuttake(true);
  intake(-20);
  wait(200, msec);
  printf("Time: %.2f", Timer.time() - start);
}

void red10() {
  double start = Timer.time();
  resetCoords(0, 0, -58.3);
  shootPreload();
  baseMove(32);
  waitBase(1500);
  // baseTurn(-27, 60, 0.3, 0, 10, false);
  baseTurn(1, 0.295, 0, 10);
  waitBase(2000);
  intake(100);
  baseMove(32);
  waitBase(2000);
  baseTurn(-92, 0.29, 0, 10);
  waitBase(2000);
  intake(-10);
  baseMove(-23.5);
  waitBase(1200);
  // baseMove(10);
  // waitBase(1000);
  // baseTurn(-49, 0 , 0.29, 0, 10, false);
  baseTurn(-136, 0.285, 0, 10);
  waitBase(1500);
  // wait(500, msec);
  // resetPrevEncd();
  // intake(0);
  resetPrevEncd();
  baseMove(62.5, 0.14, 0, 5);
  waitBase(2000);
  intake(0);
  baseMove(-40, 0.14, 0, 5);
  intake(-30);
  waitBase(1500);
  // baseTurn(69, -2, 0.33, 0, 10, false);
  baseTurn(-246, 0.285, 0, 10);
  waitBase(1500);
  // wait(500, msec);
  // resetPrevEncd();
  intake(-5);
  baseMove(98, 0.15, 0, 10);
  waitBaseNoD(2500);
  baseMove(20);
  shootBall();
  wait(50, msec);
  forceOuttake(true);
  intake(-20);
  wait(200, msec);
  printf("Time: %.2f", Timer.time() - start);
}
