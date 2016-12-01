/*
  LedBlinky.h

  Copyright (c) 2016, Biagio Montaruli

  Releases and Notes :
  - 1.0.0 => First version of Led library
  - 1.0.1 => Add a second constructor that checks the led configuration
  - 1.0.2 => Add documentation
  - 1.0.3 => Add new methods : getLedPinNumber(), getLedPinState()
  			 getLedPullType(), printLedInfo() useful for debugging
  - 1.0.4 => Improve documentation
  - 1.1.0 => Add examples and fix some mistakes
  - 1.1.1 => Fix typing mistakes in README.adoc and library.properties
  - 1.2.0 => Update Led constructor, documentation and Serial debugging
  - 1.3.0 => Change library name to LedBlinky, related files and class
  - 1.3.1 => Rename some sketches and update their documentation
*/

#ifndef LEDBLINKY_H
#define LEDBLINKY_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

// allow the use of digital pins 2 - 12 for all Arduino boards
// pin 0 and 1 are used for Serial comunication so don't use it
// instead pin 13 is used for the BUILTIN LED
#define isDigital(pin)	((pin >= 2) && (pin <= 12) ? true : false)
#if defined(__AVR_ATmega2560__) 
	#define isAnalog(pin)	((pin >= A0) && (pin <= A15) ? true : false)
#elif defined(_VARIANT_ARDUINO_DUE_X_)
	#define isAnalog(pin)	((pin >= A0) && (pin <= A11) ? true : false)
#else
	#define	isAnalog(pin)	((pin >= A0) && (pin <= A5) ? true : false)
#endif

/* Uncomment the next line of code to enable serial debugging */
// #define SERIAL_DEBUG

#if defined(SERIAL_DEBUG)
#define SERIAL_PORT Serial
#endif

#define WRONG_PIN 0

typedef enum {
	OFF = 0,
	ON = 1,
	WRONG_STATE = 3
} LedState;

typedef enum {
	PULL_DOWN = 0,
	PULL_UP = 1
} PullType;

class LedBlinky {

private :
	uint8_t _pin;
	bool _pinState;
	LedState _state;
	bool _pinPWM;
	uint8_t _brightness;
	PullType _ledPullType;
	
	void setState(uint8_t state);
	bool checkInit(void) const;
	uint8_t checkBrightness(LedState s) const;
#if defined(SERIAL_DEBUG)
	void printLedState(void) const;
	void printLedPinState(void) const;
	void printLedBrightness(void) const;
#endif
	
public :
	LedBlinky(uint8_t pin, LedState initState, PullType pull);
	LedBlinky(uint8_t pin, LedState initState);
	void begin(void) const;
	void end(void) const;
	void on(void);
	void off(void);
	void toggle(void);
	void setBrightness(uint8_t brightness = 255);
	void blink(long onDelay, long offDelay, uint8_t brightness = 255);
	bool getState(void) const;
	uint8_t getBrightness(void) const;
	uint8_t getLedPinNumber(void) const;
	bool getLedPinState(void) const;
	PullType getLedPullType(void) const;
#if defined(SERIAL_DEBUG)
	void printLedInfo(void) const;
#endif
};

#endif
