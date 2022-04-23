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
// Calvin               digital_out   H               
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
  clawFront(0, -1.82); //0 is up 1 is down
  wait(0.3, sec);
  moveForward(1.2, 100);
  clawFront(0,1.9);
  wait(0.5, sec);
  moveForward(1.6, -75); 
  turnRight(0.2);
  moveForward(0.8,50);
  backClaw(1,1);
  wait(0.5, sec);
  turnLeft(1);
  // //find location then adjust and add backclaw function here
  // clawFront(0, 0.8);
  //lift(d, -100);
  //turnRight(0.35);
  //moveForward(2,-75); //actually move backwards (negative power)
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
      begintime = time(NULL) + 4.3;
    }
    if (Controller1.ButtonDown.pressing()) {
      jimx.spin(reverse);
      jinx.spin(reverse);
      begintime = time(NULL) + 4.3;
      //2.4
    }
    if (Controller1.ButtonLeft.pressing()) {
      Calvin.set(true);
    }
    else {
      Calvin.set(false);
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