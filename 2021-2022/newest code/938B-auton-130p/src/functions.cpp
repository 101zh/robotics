#include "vex.h"
//using namespace vex;
//test

void motorLock() {
  leftFront.setStopping(hold);
  leftBack.setStopping(hold);
  rightFront.setStopping(hold);
  rightBack.setStopping(hold);
}
void motorUnlock() {
  leftFront.setStopping(coast);
  leftBack.setStopping(coast);
  rightFront.setStopping(coast);
  rightBack.setStopping(coast);
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
void moveForwardClaw(float time, int power) {
  sushiTimothy.setVelocity(100, percent);
  rightBack.setVelocity(power,percent);
  leftBack.setVelocity(power,percent);
  leftFront.setVelocity(power,percent);
  rightFront.setVelocity(power,percent);
  sushiTimothy.spinFor(reverse, 2, turns, false);
  rightBack.spin(forward);
  leftBack.spin(forward);
  rightFront.spin(forward);
  leftFront.spin(forward);
  wait(1.2, sec);
  rightBack.stop();
  leftBack.stop();
  leftFront.stop();
  rightFront.stop();
  amogus.set(true);
  rightBack.spin(reverse);
  leftBack.spin(reverse);
  rightFront.spin(reverse);
  rightBack.spin(reverse);
  rightBack.stop();
  leftBack.stop();
  leftFront.stop();
  rightFront.stop();
  wait(0.3, sec);
  rightBack.spin(reverse);
  rightFront.spin(reverse);
  leftBack.spin(forward);
  leftFront.spin(forward);  
  wait(0.2, sec);
  rightBack.stop();
  leftBack.stop();
  leftFront.stop();
  rightFront.stop();
  rightBack.spin(reverse);
  leftBack.spin(reverse);
  rightFront.spin(reverse);
  rightBack.spin(reverse);
  wait(1, seconds);
  rightBack.stop();
  leftBack.stop();
  leftFront.stop();
  rightFront.stop();
  sushiTimothy.spinFor(reverse, 1, turns);


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
  if (direction == 1.4) {
    jimx.spin(reverse);
    jinx.spin(reverse);
    wait(time, sec);
    jimx.stop();
    jinx.stop();
  }
}

//Constants
double kU = 0; //time until occilation
double tU = 0; //period of occilation
//1.8
double tunedKP = 1.8;
//0.8*ku
//kU0.53 tU0.34
//kP0.424
//tD0.0425
double kP = 0.848;
double tD = 0.0425;
double kD = 0.03604;

void pidTurn(double angle, double tolerance) {
  leftFront.setStopping(hold);
  leftBack.setStopping(hold);
  rightFront.setStopping(hold);
  rightBack.setStopping(hold);

  //Variables
  double heading = calvin.heading(deg);
  double error = heading - angle;
  //double error = calvin.heading(deg) - 360 + angle;
  double totalError = 0;
  double lastError = 0;
  double motorPower = 0;
  double lastMotorPower = 0;
  int oscillations = 0;

  double startingTime;
  double firstOscillation;
  double secondOscillation;
  timer oTimer;
  startingTime = oTimer.value();
  //Control loop //0.5, x, 0.5, 0.5, 2, 1, x, x, 0.5, 1 
  while (error < -tolerance || error > tolerance) {

    heading = calvin.heading(deg);
    error = heading - /*360 +*/ angle;
    //Always uses acute angle
    if (error > 180 ) {
      error = error - 360;
    }
    else if (error < -180) {
      error = 360 + error;
    }
    if (calvin.heading(deg) > 180 && (angle < 10 || angle > 350)){
      error = -360+calvin.heading(deg);
    }
    totalError += error;
    motorPower = kP * error + kD * (error - lastError);
    /*if ((motorPower > 0 && lastMotorPower < 0) || (motorPower < 0 && lastMotorPower > 0)) {
      oscillations++;
      switch (oscillations) {
        case 1:
          firstOscillation = oTimer.value();
          kU = firstOscillation - startingTime;
          Controller1.Screen.print(kU);
          Controller1.Screen.print("_");
          break;
        case 2:
          secondOscillation = oTimer.value();
          tU = secondOscillation - firstOscillation;
          Controller1.Screen.print(tU);
          break;
        default:
          break;
      }
    }*/
    double motorPowerAbs = motorPower;
    if ((motorPowerAbs < 0 && error > 0) || (motorPowerAbs > 0 && error < 0))
    {
      motorPowerAbs = -motorPowerAbs;
    }

    if (motorPowerAbs < 0 && motorPowerAbs > -1)
    {
      motorPowerAbs = -1;
    } 

    if (motorPowerAbs > 0 && motorPowerAbs < 1)
    {
      motorPowerAbs = 1;
    }
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
    
    Controller1.Screen.print(calvin.heading());
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
    lastMotorPower = motorPower;
    
  }

  //Debug
  leftFront.stop();
  leftBack.stop();
  rightFront.stop();
  rightBack.stop();
  Controller1.Screen.print("Loop Complete");
}

//Climb Constants
double cKP = 0.3;
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