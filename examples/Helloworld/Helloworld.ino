/*
  Helloworld
  Use the LedBlinky library to blink a led attached to digital pin 4
  
  created 2 Sept 2016
  by Biagio Montaruli

  This example code is in the public domain.
 */
#include <LedBlinky.h>

const int ledPin = 4;

LedBlinky myLed(ledPin, OFF);

void setup() {
  // enable Serial communication
  // and to print info about led initialization.
  // IMPORTANT NOTE :
  // Remember also to uncomment the line // #define SERIAL_DEBUG
  // in the Led.h header file to print debug info in the Serial Monitor
  Serial.begin(9600);
  while(!Serial) ;
  // initialize the LedBlinky library
  myLed.begin();
}

void loop() {
  // turn the led ON
  myLed.on();
  // wait for 1 second (1000 milliseconds)
  delay(1000);
  // turn the led OFF
  myLed.off();
  // wait for 1 second (1000 milliseconds)
  delay(1000);
}
