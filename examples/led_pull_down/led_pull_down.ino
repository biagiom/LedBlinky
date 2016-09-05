/*
  led_pull_down
  Use the Led library to initialize a pull-down led.
  This is a bare-minimum skecth that show you how to use a led
  connected to digital pin using a pull-down resistor.
  GND ------------/\/\/\/----------- <| ------- <==
  0V        pull-down resistor       LED      led pin
  To turn the led ON, the led pin must be set up as HIGH, instead
  to turn the led OFF, the led pin must be set up as LOW
  
  created 2 Sept 2016
  by Biagio Montaruli

  This example code is in the public domain.
 */
#include <Led.h>

const int ledPin = 4;

// create a new instance of Led library :
// ledPin is the number of the led pin
// OFF is the initial state of the led
// PULL_DOWN is the type of resistor used to connect the led
Led myLed(ledPin, OFF, PULL_DOWN);

void setup() {
  // enable Serial comunication 
  // and to print info about led initialization.
  // IMPORTANT NOTE : 
  // Remember also to uncomment the line // #define SERIAL_DEBUG
  // in the Led.h header file to print debug info in the Serial Monitor
  Serial.begin(9600);
  while(!Serial) ;
  // initialize the Led library
  myLed.begin();
  // print led info :
  // this function prints led state, led brightness and the state
  // of the led pin
  myLed.printLedInfo();
}

void loop() {
  
}
