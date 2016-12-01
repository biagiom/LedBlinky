/*
  Fade
  Use the LedBlinky library to change the led brightness
  
  created 2 Sept 2016
  by Biagio Montaruli

  This example code is in the public domain.
 */
#include <LedBlinky.h>

const int ledPin = 9;

// create a new instance of LedBlinky library :
// ledPin is the number of the led pin
// OFF is the initial state of the led
LedBlinky myLed(ledPin, OFF);

void setup() {
  /* Uncomment the following lines to enable serial communication 
     and to print info about led initialization.
     IMPORTANT NOTE : 
     Remember also to uncomment the line // #define SERIAL_DEBUG
     in the LedBlinky.h header file to print debug info in the Serial Monitor
   */
  // Serial.begin(9600);
  // while(!Serial) ;
  myLed.begin();
  /* Uncomment the following line to enable serial communication 
     and to print info about led initialization.
   */
  // myLed.printLedInfo();

  // Start to brightness 0 and increment it till the maximum value (255) 
  for(int light = 0; light < 256; light++) {
    myLed.setBrightness(light);
    delay(100);
  }
  // When the led has full brightness, start decrementing
  // the brightness till it reaches the value 0 (led is OFF)
  for(int light = 255; light >= 0; light--) {
    myLed.setBrightness(light);
    delay(100);
  }
}

void loop() {

}
