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
// rightBack            motor         18              
// leftBack             motor         17              
// rightFront           motor         15              
// leftFront            motor         2               
// Controller1          controller                    
// sushiTimothy         motor         3               
// calvin               inertial      19              
// amogus               digital_out   E               
// jinx                 motor         5               
// jimx                 motor         9               
// dn                   motor         16              
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
  // ..........................................................................
  //Calibrating
  //calvin.calibrate();
  /*while (calvin.isCalibrating()) {
    wait(100, msec);
  }*/
  sushiTimothy.setVelocity(100, percent);
  rightBack.setVelocity(100,percent);
  leftBack.setVelocity(100,percent);
  leftFront.setVelocity(100,percent);
  rightFront.setVelocity(100,percent);
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
  //Autonomous
  /*clawFront(1,2);
  moveForward(1.1, 50);
  clawFront(0,2.3);
  clawFront(1,1.1);
  turnLeft(0.55);
  moveForward(0.95, 50);
  turnRight(0.55);
  moveForward(3, 50);
  moveForward(3, -50);
  turnLeft(0.275);
  moveForward(5, 50);
  //pidTurnRight(0);
  turnRight(0.275);
  //backClaw(1,3.4);
  moveForward(3, -50);
  //backClaw(0,3.4);
  moveForward(2.5, 50);
  leftFront.setStopping(brake);
  leftBack.setStopping(brake);
  rightFront.setStopping(brake);
  rightBack.setStopping(brake);
  leftFront.stop();
  leftBack.stop();
  rightFront.stop();
  rightBack.stop();
  //turnRight(0.1);
  wait(1, seconds);
  pidTurn(90, 2);
  moveForward(4,50);
  pidTurn(180, 2);
  setVelocityAll(-100);
  rightBack.spin(forward);
  leftBack.spin(forward);
  rightFront.spin(forward);
  leftFront.spin(forward);
  wait(1.2, sec);
  rightBack.stop();
  leftBack.stop();
  leftFront.stop();
  rightFront.stop();
  pidTurn(270, 1);
  moveForward(1, 50);
  moveForward(3,50);
  climb();
  Controller1.Screen.print("Autonomouse is complete");
  Controller1.Screen.clearScreen();
  Controller1.Screen.clearLine();
  wait(4, sec);
  Controller1.Screen.print("do we ahve time to ri=nt this :!!!!!!!!! !!!!!!");*/
  //pidTurn(270, 1);


/*moveForward(2, 50);
climb();*/
  /*calvin.calibrate();
  while (calvin.isCalibrating()) {
    wait(100, msec);
  }
  moveForward(2, 50);
  climb();*/
  //pidTurnLeft(270);
  //wait(1, sec);
  //pidTurnRight(0);
  //moveForward(0.5,100); //to drive up
  //moveForward(0.5,75);
  //moveForward(0.5,50);

  //turnRight(0.36); //temp to drive into zone
  //moveForward(2,50);
  //turnRight(0.56); //how to get on platform 
  //moveForward(1, -50); 
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

void usercontrol(void) {
  sushiTimothy.setMaxTorque(100,percent);
  dn.setMaxTorque(100, percent);
  dn.setVelocity(100, percent);
  dn.setStopping(hold);
  sushiTimothy.setVelocity(100,percent);
  sushiTimothy.setStopping(hold);
  int begintime = -100;
  leftFront.setStopping(coast);
  leftBack.setStopping(coast);
  rightFront.setStopping(coast);
  rightBack.setStopping(coast);
  double left = 0;
  double right = 0;
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.
    Controller1.ButtonX.pressed(motorLock);
    Controller1.ButtonY.pressed(motorUnlock);
    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    left = Controller1.Axis3.position(percent) + Controller1.Axis1.position(percent);
    right = Controller1.Axis3.position(percent) - Controller1.Axis1.position(percent);
    rightBack.setVelocity(right, percent);
    rightFront.setVelocity(right, percent);
    leftFront.setVelocity(left, percent);
    leftBack.setVelocity(left, percent);
    rightBack.spin(forward);
    rightFront.spin(forward);
    leftBack.spin(forward);
    leftFront.spin(forward);
    //timothy is front grabber
    //chlome is lift
    if (Controller1.ButtonUp.pressing()) {
      amogus.set(true);
    }
    if (Controller1.ButtonDown.pressing()) {
      amogus.set(false);
    }
    if (time(NULL) >= begintime && time(NULL) < begintime + 20){
      jinx.stop();
      jimx.stop();
    }
    
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
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