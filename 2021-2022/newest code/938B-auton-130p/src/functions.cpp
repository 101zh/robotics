#include "vex.h"
//using namespace vex;
//test

void clampUp() {
  piston.set(false);
}
void clampDown() {
  piston.set(true);
}
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

void setVelocityAll(int velocityAll){
  rightBack.setVelocity(velocityAll, pct);
  rightFront.setVelocity(velocityAll, pct);
  leftBack.setVelocity(velocityAll, pct);
  leftFront.setVelocity(velocityAll, pct);
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
void backLift(int direction, float rotations) {
  if (direction == 0) {
    fourBar.spinFor(forward, rotations, turns);
  }
  if (direction == 1) {
    fourBar.spinFor(reverse, rotations, turns);
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
  if (direction == 1) {
    jimx.spin(reverse);
    jinx.spin(reverse);
    wait(time, sec);
    jimx.stop();
    jinx.stop();
  }
}

//Constants
double kP = 1;
double kI = 0;
double kD = 0;

void pidTurn(double angle, double tolerance) {

//Variables
double heading = (RightEncoder.position(deg) - LeftEncoder.position(deg)) * 0.0174533 * 2.75 / 15.25;
double error = angle - heading;
//double error = calvin.heading(deg) - 360 + angle;
double totalError = 0;
double lastError = 0;
double motorPower = 0;

  //Control loop //0.5, x, 0.5, 0.5, 2, 1, x, x, 0.5, 1 
  while (error < -tolerance || error > tolerance) {

    heading = (RightEncoder.position(deg) - LeftEncoder.position(deg)) * 0.0174533 * 2.75 / 15.25;
    error = angle - heading;
    //Always uses acute angle
    if (error > M_PI ) {
      error = error - 2 * M_PI;
    }
    else if (error < -M_PI) {
      error = 2* M_PI + error;
    }
    if ((RightEncoder.position(deg) - LeftEncoder.position(deg)) * 0.0174533 * 2.75 / 15.25 > M_PI && (angle < 0.1 || angle > 2 * M_PI - 0.1)){
      error = -2 * M_PI+(RightEncoder.position(deg) - LeftEncoder.position(deg)) * 0.0174533 * 2.75 / 15.25;
    }
    totalError += error;
    motorPower = (error * kP + totalError * kI + (error - lastError) * kD);
    double motorPowerAbs = motorPower;
    if ((motorPowerAbs < 0 && error > 0) || (motorPowerAbs > 0 && error < 0))
    {
      motorPowerAbs = -motorPowerAbs;
    }

    /*if (motorPowerAbs < 0 && motorPowerAbs > -1)
    {
      motorPowerAbs = -1;
    } 

    if (motorPowerAbs > 0 && motorPowerAbs < 1)
    {
      motorPowerAbs = 1;
    }*/
    


    /*if (motorPower > 20) {
      motorPower = 20;
    }
    if (motorPower < -20) {
      motorPower = -20;
    }*/

    leftFront.spin(reverse, motorPower, percent);
    leftBack.spin(reverse, motorPower, percent);
    rightFront.spin(forward, motorPower, percent);
    rightBack.spin(forward, motorPower, percent);
    
    Controller1.Screen.print((RightEncoder.position(deg) - LeftEncoder.position(deg)) * 0.0174533 * 2.75 / 15.25);
    Controller1.Screen.print("er");
    Controller1.Screen.print(error);
    Controller1.Screen.print("te");
    Controller1.Screen.print(totalError);
    Controller1.Screen.print("le");
    Controller1.Screen.print(lastError);
    Controller1.Screen.print(motorPower);
    Controller1.Screen.clearScreen();
    Controller1.Screen.clearLine();
    lastError = error;
    
  }

  //Debug
  leftFront.stop();
  leftBack.stop();
  rightFront.stop();
  rightBack.stop();
  Controller1.Screen.print("Loop Complete");
}

//Climb Constants
double cKP = 0.4;
double cKI = 0;
double cKD = 0.2;

void climb() {
  //Variables
double error = -calvin.pitch(deg);
double totalError = 0;
double lastError = 0;
double motorPower = 0;

leftFront.setStopping(hold);
leftBack.setStopping(hold);
rightFront.setStopping(hold);
rightBack.setStopping(hold);
  //Control loop //0.5, x, 0.5, 0.5, 2, 1, x, x, 0.5, 1 
  while (error < -2 || error > 2) {
    

    /*leftFront.stop();
    leftBack.stop();
    rightFront.stop();
    rightBack.stop();
    wait(100, msec);*/

    error = -calvin.pitch(deg);
    totalError += error;
    motorPower = -(error * cKP + totalError * cKI + (error - lastError) * cKD);

    /*if (motorPower > 20) {
      motorPower = 20;
    }
    if (motorPower < -20) {
      motorPower = -20;
    }*/

    leftFront.spin(forward, motorPower, percent);
    leftBack.spin(forward, motorPower, percent);
    rightFront.spin(forward, motorPower, percent);
    rightBack.spin(forward, motorPower, percent);
    
    Controller1.Screen.print(calvin.pitch());
    Controller1.Screen.print("er");
    Controller1.Screen.print(error);
    Controller1.Screen.print("te");
    Controller1.Screen.print(totalError);
    Controller1.Screen.print("le");
    Controller1.Screen.print(lastError);
    Controller1.Screen.print(motorPower);
    Controller1.Screen.clearScreen();
    Controller1.Screen.clearLine();

    lastError = error;
    
  }

  //Debug
  leftFront.stop();
  leftBack.stop();
  rightFront.stop();
  rightBack.stop();
  Controller1.Screen.print("Loop Complete");
}