/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       clarkwang                                                 */
/*    Created:      Fri May 19 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LeftBwd              motor         1               
// RightBwd             motor         15              
// Cata                 motor         18              
// LeftFwd              motor         12              
// LeftCtr              motor         13              
// RightFwd             motor         16              
// RightCtr             motor         17              
// Limit                limit         H               
// PistonThingy         digital_out   G               
// Motor11              motor         11              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

vex::competition Competition;

// Define a boolean variable for safe drive mode
bool safeDriveMode = false;

int motorTempLF = 0;
int motorTempLC = 0;
int motorTempLB = 0;

int motorTempRF = 0;
int motorTempRC = 0;
int motorTempRB = 0;

bool lockedSwitch = false;

bool fly = false;

// Define a boolean variable for extend
bool extend = false;

void switchMode() {
  // Toggle safe drive mode
  safeDriveMode = !safeDriveMode;

  // Clear the screen
  Controller1.Screen.clearScreen();

  // Print the current mode
  Controller1.Screen.newLine();
  Controller1.Screen.print(safeDriveMode ? "Safe Drive Mode" : "Normal Mode");
}

void toggleFly() {
  fly = !fly;
}

void toggleExtend() {
  // Toggle extend
  extend = !extend;
}

void getTemperature() {
  while (1) {
    motorTempLF = LeftFwd.temperature(percent);
    motorTempLC = LeftCtr.temperature(percent);
    motorTempLB = LeftBwd.temperature(percent);
    motorTempRF = RightFwd.temperature(percent);
    motorTempRC = RightCtr.temperature(percent);
    motorTempRB = RightBwd.temperature(percent);

    task::sleep(1000);
  }
}

void printStuff() {
  Controller1.Screen.clearScreen();

  // Print the current mode
  Controller1.Screen.newLine();
  Controller1.Screen.print(safeDriveMode ? "Safe Drive Mode" : "Normal Mode");
}

void usercontrol(void) {
  while (1) {
    double move = (Controller1.Axis3.position(percent)) *
                  (Controller1.Axis3.position(percent)) *
                  (Controller1.Axis3.position(percent)) / 10000;
    double turn = (Controller1.Axis1.position(percent)) *
                  (Controller1.Axis1.position(percent)) *
                  (Controller1.Axis1.position(percent)) / 10000;

    double leftPower = move + turn*(safeDriveMode?0.6:0.85);
    double rightPower = move - turn*(safeDriveMode?0.6:0.85);

    // Set the motor speeds
    LeftFwd.spin(forward, -rightPower, percent);
    LeftCtr.spin(forward, -rightPower, percent);
    LeftBwd.spin(forward, -rightPower, percent);
    RightFwd.spin(forward, -leftPower, percent);
    RightCtr.spin(forward, -leftPower, percent);
    RightBwd.spin(forward, -leftPower, percent);

    Cata.setVelocity(100, rpm);

    if (fly) {
      // Motor11.spin(forward, -100, percent);
      Motor11.spin(forward, 100, percent);
    }
    else {
      Motor11.stop(); 
    }

    if (Controller1.ButtonR1.pressing()) {
      Cata.spin(reverse);
      lockedSwitch = false;
    } else if (Controller1.ButtonR2.pressing() && lockedSwitch == true) {
      Cata.spin(forward, 40, percent);
    } else if (!Limit.pressing() && !Controller1.ButtonR2.pressing()) {
      Cata.spin(forward);
      lockedSwitch = false;
    } else {
      Cata.stop();
      Cata.setStopping(hold);
      lockedSwitch = true;
    }

    // Check if extend is true or false and control the pneumatics accordingly
    if (extend) {
      // Code to extend the pneumatics
      PistonThingy.set(true);
    } else {
      // Code to retract the pneumatics
      PistonThingy.set(false);
    }

    printStuff();

    // Add a delay to prevent the loop from running too fast
    task::sleep(50);
  }
}

void auton(void){
  //make robot drive forward for one second
  int driveSpeed = 50; // You can adjust this speed as needed

  // Spin the motors to move forward
  LeftFwd.spin(forward, driveSpeed, percent);
  LeftCtr.spin(forward, driveSpeed, percent);
  LeftBwd.spin(forward, driveSpeed, percent);
  RightFwd.spin(forward, driveSpeed, percent);
  RightCtr.spin(forward, driveSpeed, percent);
  RightBwd.spin(forward, driveSpeed, percent);

  // Wait for one second (1800 milliseconds)
  task::sleep(1800);

  // Stop all the motors
  LeftFwd.stop();
  LeftCtr.stop();
  LeftBwd.stop();
  RightFwd.stop();
  RightCtr.stop();
  RightBwd.stop();
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  Competition.drivercontrol(usercontrol);
  Competition.autonomous(auton);
  // Set the callback function for the A button
  Controller1.ButtonY.pressed(switchMode);
  // Set the callback function for the A button to toggle extend
  Controller1.ButtonA.pressed(toggleExtend);

  Controller1.ButtonL1.pressed(toggleFly);

  // Create a new thread to print the temperature every second
  thread printTempTask(getTemperature);
}
