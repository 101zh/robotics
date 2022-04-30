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
// rightBack            motor         2               
// leftBack             motor         15              
// rightFront           motor         17              
// leftFront            motor         18              
// Controller1          controller                    
// sushiTimothy         motor         3               
// jimx                 motor         6               
// calvin               inertial      19              
// fourBar              motor         16              
// piston               digital_out   E               
// jinx                 motor         1               
// LeftEncoder          encoder       A, B            
// RightEncoder         encoder       G, H            
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
  piston.set(false);
  calvin.calibrate();
  while (calvin.isCalibrating()) {
    wait(100, msec);
  }
  //Autonomous
  //Picks up blue goal
  clawFront(1,2);
  moveForward(1.1, 50);
  clawFront(0, 1.2);
  //clawFront(1,1.1);
  //Pushes first yellow goal
  wait(0.2, sec);
  turnLeft(0.6);
  moveForward(0.9, 50);
  turnRight(0.52);
  moveForward(3, 50);
  moveForward(3, -50);
  wait(0.2, sec);
  //Pushes second yellow goal
  turnLeft(0.32);
  moveForward(5, 50);
  //moveForward(1, -50);
  //Pushes third yellow goal
  turnRight(0.4);
  moveForward(3, -50);
  moveForward(3, 50);
  turnRight(0.6);
  clawFront(1, 1.2);
  moveForward(1, -50);
  piston.set(true);
  turnLeft(0.6);
  moveForward(5, -50);


  //pidTurn(M_PI / 2, 0.05);

  //piston.set(true);
  //moveForward(1.5, 50);
  //clawFront(0, 0.8);
  //turnLeft(0.55);
  //moveForward(3, 50);
  //piston.set(false);
  //moveForward(3, -50);
  //clawFront(1, 1.5);
  //turnLeft(0.55);
  //moveForward(2, 50);
  //clawFront(0, 2);
  //turnLeft(0.55);
  //moveForward(5, 50);
  //clawFront(1, 2);
  //moveForward(5,-50);

  /*//Drives across
  leftFront.setStopping(brake);
  leftBack.setStopping(brake);
  rightFront.setStopping(brake);
  rightBack.setStopping(brake);
  leftFront.stop();
  leftBack.stop();
  rightFront.stop();
  rightBack.stop();
  wait(1, seconds);
  pidTurn(90, 2);
  moveForward(4,50);
  //Align with platform
  wait(0.2, sec);
  pidTurn(180, 5);
  wait(0.2, sec);
  setVelocityAll(-100);
  rightBack.spin(forward);
  leftBack.spin(forward);
  rightFront.spin(forward);
  leftFront.spin(forward);
  wait(1.2, sec);
  rightBack.stop();
  leftBack.stop();
  leftFront.stop();
  rightFront.stop(); //backwards
  wait(0.2, sec);
  moveForward(1, -50);
  pidTurn(300, 3);
  wait(0.2, sec);
  moveForward(1.5, 25);
  wait(0.2, sec);
  pidTurn(270, 1.5);
  wait(0.2, sec);
  //Balances
  moveForward(3,50);
  climb();
  Controller1.Screen.print("Autonomouse is complete");
  Controller1.Screen.clearScreen();
  Controller1.Screen.clearLine();
  wait(4, sec);
  Controller1.Screen.print("do we ahve time to ri=nt this :!!!!!!!!! !!!!!!");*/


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
  sushiTimothy.setVelocity(100,percent);
  sushiTimothy.setStopping(hold);
  fourBar.setMaxTorque(100,percent);
  fourBar.setVelocity(100,percent);
  fourBar.setStopping(hold);
  int begintime = -100;
  // User control code here, inside the loop
  bool pistonState = false;
  while (1) {
    Controller1.ButtonUp.pressed(clampUp);
    Controller1.ButtonDown.pressed(clampDown);
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    rightBack.setVelocity(Controller1.Axis2.position(percent),percent);
    rightFront.setVelocity(Controller1.Axis2.position(percent), percent);
    leftFront.setVelocity(Controller1.Axis3.position(percent), percent);
    leftBack.setVelocity(Controller1.Axis3.position(percent), percent);
    rightBack.spin(forward);
    rightFront.spin(forward);
    leftBack.spin(forward);
    leftFront.spin(forward);
    //timothy is front grabber
    //chlome is lift
    if (Controller1.ButtonUp.pressing()) {
      jimx.spin(forward);
      jinx.spin(forward);
      begintime = time(NULL) + 2.7;
    }
    if (Controller1.ButtonDown.pressing()) {
      jimx.spin(reverse);
      jinx.spin(reverse);
      begintime = time(NULL) + 2.7;
      //2.4
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