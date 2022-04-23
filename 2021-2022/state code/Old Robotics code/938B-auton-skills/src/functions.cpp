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
  if (direction == 0) { //up
    jimx.spin(forward);
    jinx.spin(forward);
    wait(time, sec);
    jimx.stop();
    jinx.stop();
  }
  if (direction == 1) { //down
    jimx.spin(reverse);
    jinx.spin(reverse);
    wait(time, sec);
    jimx.stop();
    jinx.stop();
  }
}

void setVelocityAll(int velocityAll){
  rightBack.setVelocity(velocityAll, pct);
  rightFront.setVelocity(velocityAll, pct);
  leftBack.setVelocity(velocityAll, pct);
  leftFront.setVelocity(velocityAll, pct);
}

void degreeTurn(int degrees){
  leftFront.spinTo(degrees, deg, false);
  leftBack.spinTo(degrees, deg, false);
  rightFront.spinTo(-degrees, deg, false);
  rightBack.spinTo(-degrees, deg, false);
}
void pidTurnTo(int degrees){
  rightBack.spin(reverse);
  leftBack.spin(forward);
  rightFront.spin(reverse);
  leftFront.spin(reverse);
  setVelocityAll(100);
  while (calvin.heading(deg) < degrees - 1 || calvin.heading(deg) > degrees + 1){
    rightBack.setVelocity(((calvin.heading(deg)-degrees)/2), pct);
    rightFront.setVelocity((calvin.heading(deg)-degrees)/2, pct);
    leftBack.setVelocity((calvin.heading(deg)-degrees)/-2, pct);
    leftFront.setVelocity((calvin.heading(deg)-degrees)/-2, pct);
    Brain.Screen.clearLine();
    wait(100, msec);
    Brain.Screen.print(calvin.heading(deg));
    Controller1.Screen.clearLine();
    wait(100, msec);
    Controller1.Screen.print(calvin.heading(deg));
  }
  rightBack.stop();
  rightFront.stop();
  leftBack.stop();
  leftFront.stop();
}

void pLineFollow(int degrees, int pwr, int sec){
  rightBack.spin(reverse);
  leftBack.spin(forward);
  rightFront.spin(reverse);
  leftFront.spin(reverse);
  setVelocityAll(100);
  int endTime = time(NULL) + sec;
  Controller1.Screen.print(endTime-time(NULL));
  while (time(NULL) < endTime){
    rightBack.setVelocity(((calvin.heading(deg)-degrees+pwr)/2), pct);
    rightFront.setVelocity((calvin.heading(deg)-degrees+pwr)/2, pct);
    leftBack.setVelocity(((calvin.heading(deg)-degrees)*-1+pwr)/2, pct);
    leftFront.setVelocity(((calvin.heading(deg)-degrees)*-1+pwr)/2, pct);
    Controller1.Screen.clearLine();
    wait(100, msec);
    Controller1.Screen.print(calvin.heading(deg));
  }
  rightBack.stop();
  rightFront.stop();
  leftBack.stop();
  leftFront.stop();
}