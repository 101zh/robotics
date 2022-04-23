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
// rightBack            motor         4               
// leftBack             motor         13              
// rightFront           motor         11              
// leftFront            motor         20              
// Controller1          controller                    
// sushiTimothy         motor         18              
// jimx                 motor         17              
// jinx                 motor         16              
// calvin               inertial      19              
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
  /*clawFront(1,2);
  moveForward(1,50);
  clawFront(0,2.3);
  clawFront(1,1.1);
  turnLeft(0.21);
  moveForward(3.8, 50);
  moveForward(0.3, -50);
  turnLeft(0.62);
  moveForward(3.2, 50);
    turnLeft(0.36); //temp to drive into zone
    moveForward(2,50);
      //turnRight(0.56); //how to get on platform 
      //moveForward(1, -50); */
  calvin.calibrate();
  while(calvin.isCalibrating()){
    wait(100, msec);
  }
  pidTurnTo(90);
  //everything is broken
  /*
  setVelocityAll(100);
  clawFront(1,2);
  moveForward(1.5,50);
  clawFront(0,2.3);
  pidTurnTo(-90);
  moveForward(2, 50);
  pidTurnTo(0);
  clawFront(3,50);
  pidTurnTo(0);
  clawFront(3,-50);
  pidTurnTo(-40);
  moveForward(4,50);
  backClaw(1,4.3);
  pLineFollow(0,-50,4);
  backClaw(0,4.3);
  pLineFollow(0,50,4);
  pLineFollow(90,50, 4);
  */
  


  //test 
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
  int begintime = -100;
  // User control code here, inside the loop
  while (1) {
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
      begintime = time(NULL) + 3.4;
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
    Brain.Screen.print(calvin.orientation(yaw, degrees));
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