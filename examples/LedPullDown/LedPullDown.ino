/*
  LedPullDown
  This is a bare-minimum skecth that show you how to use 
  the LedBlinky library to control a led connected to the 
  digital pin 4 using a pull-down resistor.
  GND ------------/\/\/\/----------- <| ------- <==
  0V        pull-down resistor       LED      led pin
  To turn the led ON, the led pin must be set up as HIGH, instead
  to turn the led OFF, the led pin must be set up as LOW
  
  created 2 Sept 2016
  by Biagio Montaruli

  This example code is in the public domain.
 */
#include <LedBlinky.h>

const int ledPin = 4;

// create a new instance of LedBlinky library :
// ledPin is the number of the led pin
// OFF is the initial state of the led
// PULL_DOWN is the type of resistor used to connect the led
LedBlinky myLed(ledPin, OFF, PULL_DOWN);

void setup() {
  // enable Serial communication 
  // and to print info about led initialization.
  // IMPORTANT NOTE : 
  // Remember also to uncomment the line // #define SERIAL_DEBUG
  // in the LedBlinky.h header file to print debug info in the Serial Monitor
  Serial.begin(9600);
  while(!Serial) ;
  // initialize the LedBlinky library
  myLed.begin();
  // print led info :
  // the printLedInfo() method prints led state, led brightness 
  // and the state of the led pin
  #ifdef SERIAL_DEBUG
  myLed.printLedInfo();
  #endif
}

void loop() {
  
}
