#include "vex.h"
#include "mech-lib.h"

const double SHOOTER_BALL_THRESHOLD = 70, ROUTER_BALL_THRESHOLD = 67;

double defaultShootSpeed = 100, defaultIndexSpeed = 100;

bool forcedOuttake = false;
bool shootTrigger = false;
bool loaded = false;
bool autoIndex = true;

int indexerControl() {
  Indexer.spin(fwd, defaultIndexSpeed, pct);
  while(true) {
    if(autoIndex) {
      // printf("sensors %d, %d\n", ShooterLine.value(pct), IndexerLine.value(pct));
      if(shootTrigger) Indexer.spin(fwd, defaultIndexSpeed, pct);
      else if(forcedOuttake) Indexer.spin(fwd, -defaultIndexSpeed, pct);
      else {
        if(ShooterLine.value(pct) < SHOOTER_BALL_THRESHOLD && IndexerLine.value(pct) < ROUTER_BALL_THRESHOLD) {
          Indexer.stop(hold);
          loaded = true;
        }else {
          Indexer.spin(fwd, defaultIndexSpeed, pct);
          loaded = false;
        }
      }
    }
    wait(5, msec);
  }
}

bool isLoaded() {
  return ShooterLine.value(pct) < SHOOTER_BALL_THRESHOLD;
}

void waitShooter() {
  // while(!isLoaded()) delay(5);
  while(isLoaded()) wait(5, msec);
  while(!isLoaded()) wait(5, msec);
  // while(shooterLine.get_value() < SHOOTER_BALL_THRESHOLD) delay(5);
  // while(shootTrigger) delay(5);
  // while(shooterLine.get_value() < SHOOTER_BALL_THRESHOLD) delay(5);
}

// bool autoShoot = true;
int shooterControl() {
  while(true) {
    if(autoIndex) {
      if(shootTrigger) {
        Shooter.spin(fwd, defaultShootSpeed, pct);
        waitShooter();
        // while(Controller1.ButtonR1.pressing()) wait(5, msec);
        shootTrigger = false;
      }else {
        Shooter.stop(brake);
      }
    }
  }
}

void shootBall() {
  shootTrigger = true;
}

void forceOuttake(bool value) {
  forcedOuttake = value;
}


void waitLoaded() {
  while(IndexerLine.value(pct) > ROUTER_BALL_THRESHOLD) wait(5, msec);
}

void intake(double speed) {
  LRoller.spin(fwd, speed, pct);
  RRoller.spin(fwd, speed, pct);
}
