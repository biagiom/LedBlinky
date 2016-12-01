/*
  LedPullUp.
  This is a bare-minimum skecth that show you how to use 
  the LedBlinky library to control a led connected to 
  the digital pin 4 using a pull-up resistor.
    VCC ------------/\/\/\/----------- |> -----------<==
  5V/3.3V        pull-up resistor      LED      led pin
  To turn the led ON, the led pin must be set up as LOW, instead
  to turn the led OFF, the led pin must be set up as HIGH
  
  created 2 Sept 2016
  by Biagio Montaruli

  This example code is in the public domain.
 */
#include <LedBlinky.h>

const int ledPin = 4;

// create a new instance of LedBlinky library :
// ledPin is the number of the led pin
// ON is the initial state of the led
// PULL_UP is the type of resistor used to connect the led
LedBlinky myLed(ledPin, ON, PULL_UP);
 
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
  // print some info about the led 
  Serial.print("Led state = ");
  Serial.println(myLed.getState());
  Serial.print("Led brightness = ");
  Serial.println(myLed.getBrightness());
  Serial.print("Led pin number = ");
  Serial.println(myLed.getLedPinNumber());
  Serial.print("Led pin state = ");
  Serial.println(myLed.getLedPinState());
  Serial.print("Led pull type = ");
  Serial.println(myLed.getLedPullType());
}

void loop() {

}
