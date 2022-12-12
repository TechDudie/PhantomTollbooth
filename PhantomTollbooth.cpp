#pragma region VEXcode Generated Robot Configuration

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#include "vex.h"

using namespace vex;

brain Brain;

#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)

motor Motor1 = motor(PORT1, ratio36_1, false);

bumper BumperA = bumper(Brain.ThreeWirePort.A);
optical Optical2 = optical(PORT2);
led LEDB = led(Brain.ThreeWirePort.B);
led LEDD = led(Brain.ThreeWirePort.D);

#pragma endregion VEXcode Generated Robot Configuration

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       PhantomTollbooth.v5cpp                                    */
/*    Author:       TechnoDot                                                 */
/*    Created:      12/06/22                                                  */
/*    Description:  Robotics Hour 2 Final Project - Tollbooth Source Code     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include <string>

using namespace vex;

bool gate = false;
int dollars = 5;
int ids[10] = {};
int carno = 0;
int carid = 0;

void openGate() {
  for (int i=0; i<10; i++) {
    Brain.Screen.drawRectangle(i * 30 + 5, 185, 20, 50);
    Brain.Screen.setCursor(11, i * 3 + 2);
    Brain.Screen.print(i);
  }
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Enter Student ID: ");
  for (int i=0; i<7; i++) {
    while (1) {
      if (Brain.Screen.pressing()) {
        int number = (int)Brain.Screen.xPosition() / 30;
        Brain.Screen.print(number);
        wait(0.5, seconds);
        carid = carid + number * pow(10, 7 - i);
        break;
      }
    }
  }
  carid = (int)carid / 10;
  if (carid == 0) {
    Brain.Screen.newLine();
    for (int i : ids) {
      Brain.Screen.print(i);
      Brain.Screen.newLine();
    }
    wait(10, seconds);
    Brain.Screen.clearScreen();
    return;
  }
  ids[carno] = carid;
  carid = 0;
  carno++;
  Brain.Screen.newLine();
  Brain.Screen.print("$");
  Brain.Screen.print(dollars);
  Brain.Screen.print(" has been charged to your account.");
  Brain.Screen.newLine();
  Brain.Screen.print("You may pass.");
  if (gate == false) {
    Motor1.spinFor(forward, 105, degrees);
  }
  gate = true;
  wait(3, seconds);
  LEDD.off();
  LEDB.on();
}

void closeGate() {
  LEDB.off();
  LEDD.on();
  wait(3, seconds);
  if (gate == true) {
    Motor1.spinFor(reverse, 105, degrees);
  }
  gate = false;
  Brain.Screen.clearScreen();
}

void opticalCallback() {
  while (1) {
    if (Optical2.isNearObject()) {
      closeGate();
    }
  }
}

int main() {
  LEDB.off();
  LEDD.on();
  Motor1.setStopping(brake);
  Motor1.stop();
  Brain.Screen.print("Welcome to the Phantom Tollbooth.");
  Brain.Screen.newLine();
  Brani.Screen.print("Code by TechnoDot, build by Tech and Coleslaw.")
  Brain.Screen.newLine();
  Brain.Screen.print("Calibrate the motor arm, and then press.");
  Brain.Screen.newLine();
  while (1) {
    if (BumperA.pressing()) {
      Brain.Screen.print("Phantom Tollbooth activated.");
      break;
    }
  }
  wait(2, seconds);
  Brain.Screen.clearScreen();
  BumperA.pressed(openGate);
  thread opticalThread = thread(opticalCallback);
}
