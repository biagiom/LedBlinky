/*
  Blink
  Use the LedBlinky library to blink a led connected to the digital PWM
  pin 9. You can use a pull-up resistor or a pull-down resistor
  to attach the led to pin 9. The brightness of the led is controlled
  by a pot trimmer attached to analog pin A0

  Hardware:
  * Potentiometer connected to analog pin A0
  * Led connected to PWM pin 9

  created 1 Sept 2016
  by Biagio Montaruli

  This example code is in the public domain.
 */
#include <LedBlinky.h>

const int ledPin = 9;
const int potPin = A0;

// create a new instance of LedBlinky library :
// ledPin is the number of the led pin
// OFF is the initial state of the led
LedBlinky myLed(ledPin, OFF);

void setup() {
  // start the LedBlinky library
  myLed.begin();
  // set the pot pin as INPUT
  pinMode(potPin, INPUT);
}

void loop() {
  // set the time period :
  // during the time period 'delayOn' the led is ON, instead
  // during the time period 'delayOff' the led is OFF
  int delayOn = 1000, delayOff = 1000;
  // read a new value from the potentiometer to set the led brightness
  byte light = analogRead(potPin);
  // blink the led
  myLed.blink(delayOn, delayOff, light);
}
