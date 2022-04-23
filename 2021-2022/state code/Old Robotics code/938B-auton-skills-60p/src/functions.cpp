#include "vex.h"
//using namespace vex;



void moveForward(float time, int power) {
  rightBack.setVelocity(power,percent);
  leftBack.setVelocity(power,percent);
  leftFront.setVelocity(power,percent);
  rightFront.setVelocity(power,percent);
  rightBack.spin(forward);
  leftBack.spin(forward);
  rightFront.spin(forward);
  leftFront.spin(forward);
  wait(time, sec);
  rightBack.stop();
  leftBack.stop();
  leftFront.stop();
  rightFront.stop();
}

void turnLeft(float time) {
  rightBack.setVelocity(50,percent);
  leftBack.setVelocity(50,percent);
  leftFront.setVelocity(50,percent);
  rightFront.setVelocity(50,percent);
  rightBack.spin(forward);
  rightFront.spin(forward);
  leftBack.spin(reverse);
  leftFront.spin(reverse);  
  wait(time, sec);
  rightBack.stop();
  leftBack.stop();
  leftFront.stop();
  rightFront.stop();
}

void turnRight(float time) {
  rightBack.setVelocity(50,percent);
  leftBack.setVelocity(50,percent);
  leftFront.setVelocity(50,percent);
  rightFront.setVelocity(50,percent);
  rightBack.spin(reverse);
  rightFront.spin(reverse);
  leftBack.spin(forward);
  leftFront.spin(forward);  
  wait(time, sec);
  rightBack.stop();
  leftBack.stop();
  leftFront.stop();
  rightFront.stop();
}

// void lift(float time, int power) {
//   tacoChlome.setVelocity(power,percent);
//   tacoChlome.spin(forward);
//   wait(time, sec);
//   tacoChlome.stop();
// }

void clawFront(int direction, float rotations){
  if (direction == 0) { //up
    sushiTimothy.spinFor(forward, rotations, turns);
  }
  if (direction == 1) { //down
    sushiTimothy.spinFor(reverse, rotations, turns);
  }
}

void backClaw(int direction, float time){
  jinx.setStopping(hold);
  jimx.setStopping(hold);
  if (direction == 0) {
    jimx.spin(forward);
    jinx.spin(forward);
    wait(time, sec);
    jimx.stop();
    jinx.stop();
  }
  if (direction == 1) {
    jimx.spin(reverse);
    jinx.spin(reverse);
    wait(time, sec);
    jimx.stop();
    jinx.stop();
  }
}