/*
  LedBlinky.cpp

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

#include "LedBlinky.h"

/**************************************** CONSTRUCTORS *******************************************/

/** LedBlinky() : Constructor of LedBlinky class
 *  @brief Constructor to initialize the data members of LedBlinky class
 *  @param pin : the led pin
 *  @param initState : set the initial state of the led
 *                     initState can be ON or OFF
 *  @param pull : the configuration of the led :
 *                a led can be connected to a digital or analog pin using a
 *                pull-down or a pull-up resistor
 *
 *  Some notes about a led's configurations :
 *  > Led is ON if  : 1) has pull-down resistor and pin is HIGH
 *                    2) has pull-up resistor and pin is LOW
 *
 *  > Led is OFF if : 1) has pull-down resistor and pin is LOW
 *                    2) has pull-up resistor and pin is HIGH
 */
LedBlinky::LedBlinky(uint8_t pin, LedState initState, PullType pull) {
	bool checkPin = ((isDigital(pin) || isAnalog(pin)) && ((initState == ON) || (initState == OFF)));
	if(checkPin) {
		_pin = pin;
		_pinPWM = digitalPinHasPWM(pin);
		
		if(initState == ON || initState == OFF) {
			if(pull == PULL_DOWN)
				_pinState = HIGH;
			else
				_pinState = LOW;
		
			_state = initState;
			_brightness = checkBrightness(_state);
		}
		else {
			_pinState = LOW;
			_state = WRONG_STATE;
			_brightness = 0;
		}
	
		_ledPullType = pull;
	}
	else {
		_pin = WRONG_PIN;
		_pinState = LOW;
		_state = OFF;
		_pinPWM = false;
		_brightness = 0;
		_ledPullType = PULL_DOWN;
	}
}

/** LedBlinky() : Constructor (Overloading) of LedBlinky class
 *  @brief Constructor to initialize the data members of LedBlinky class
 *  @param pin : the led pin
 *  @param initState : set the initial state of the led, initState can be ON or OFF
 *  @note This constructor requires only the led pin and the initial state used
 *        to initialize the led and it check if the led is attached to its pin
 *        with a pull-up or a pull-down resistor
 */
LedBlinky::LedBlinky(uint8_t pin, LedState initState) {
	// check if the led pin is a valid digital pin or a valid analog pin
	bool checkPin = (isDigital(pin) || isAnalog(pin));
	// external resistor used to connect the led to an Arduino pin
	bool pullType;
	// if led pin is a valid digital or analog pin and check if initState is a valid state
	if(checkPin && ((initState == ON) || (initState == OFF))) {
		_pin = pin;
		// disable the internal PULL-UP resistor to read the actual pin state
		digitalWrite(_pin, LOW);
		// set led pin as input
		pinMode(_pin, INPUT);
		// read the led state
		pullType = digitalRead(_pin);
		// if external PULL-UP resistor is enabled, the led anode is connected to VCC
		// with the pull-up resistor and so digitalRead() returns HIGH (1)
		// VCC -------/\/\/\/\-------|>-------- <==
		// 5V         pull-up       LED        led pin
		// To turn the led ON, the led pin must be set up as LOW, instead
		// to turn the led OFF, the led pin must be set up as HIGH
		if(pullType == PULL_UP) {
			_ledPullType = PULL_UP;
			if(initState == ON) {
				_pinState = LOW;
				_state = initState;
			}
			else {
				_pinState = HIGH;
				_state = initState;
			}
		}
		// else led anode is connected to led pin and cathode is connected to GND
		// with a PULL-DOWN resistor and so digitalRead() returns LOW (0) :
		// GND -------/\/\/\/------- <| ------ <==
		// 0V        pull-down       LED      led pin
		// To turn the led ON, the led pin must be set up as HIGH, instead
		// to turn the led OFF, the led pin must be set up as LOW
		else {
			_ledPullType = PULL_DOWN;
			if(initState == ON) {
				_pinState = HIGH;
				_state = initState;
			}
			else {
				_pinState = LOW;
				_state = initState;
			}
		}
		
		// check if the led pin is also a PWM pin in order to set the brightness of the led
		_pinPWM = digitalPinHasPWM(pin);
		// set the initial brightness (255 if the led is ON or 0 if the led is OFF)
		_brightness = checkBrightness(_state);
	}
	// else set _pin to WRONG_PIN (0) => you have choosed a wrong pin
	else {
		_pin = WRONG_PIN;
		// assume by default led pin is LOW
		_pinState = LOW;
		_state = WRONG_STATE;
		_pinPWM = false;
		_brightness = 0;
		// assume by default led uses pull-down resistor
		_ledPullType = PULL_DOWN;
	}
}

/**************************************** PRIVATE METHODS ****************************************/

/** checkInit()
 *  @brief Private method that checks if the pin and the initial state of the led 
 *         have been set correctly
 *  @param void
 *  @return true if pin and initial state have been set up correctly,
 *          otherwise this method returns false 
 */
inline bool LedBlinky::checkInit(void) const {
	if((_pin != WRONG_PIN) && (_state != WRONG_STATE))
		return true;
	else
		return false;
}

/** checkBrightness()
 *  @brief Private method that sets up the initial value of led brightness during
 *         the LedBlinky constructor call, according to the initial led state
 *  @param s : initial led state
 *  @return the brightness initial value 
 */
inline uint8_t LedBlinky::checkBrightness(LedState s) const {
	if(s == ON)
		return 255;
	else
		return 0;
}

/** setState()
 *  @brief Private method used to set the led state
 *  @param state : used to set up the current led state
 */
void LedBlinky::setState(uint8_t state) {
	_state = (LedState) state;
	if(checkInit()) {
		if(_ledPullType == PULL_DOWN) {
			if(state == ON) {
				_pinState = HIGH;
				digitalWrite(_pin, _pinState);
			}
			else {
				_pinState = LOW;
				digitalWrite(_pin, _pinState);
			}
		}
		else {
			if(state == ON) {
				_pinState = LOW;
				digitalWrite(_pin, _pinState);
			}
			else {
				_pinState = HIGH;
				digitalWrite(_pin, _pinState);
			}
		}
		
		_brightness = checkBrightness(_state);
#if defined(SERIAL_DEBUG)
		printLedPinState();
		printLedState();
#endif 
	}
}

#if defined(SERIAL_DEBUG)

/** printLedState()
 *  @brief Public method that prints led state
 *  @param void 
 */
inline void LedBlinky::printLedState(void) const {
	SERIAL_PORT.print("Led connected to pin ");
	SERIAL_PORT.print(_pin);
	SERIAL_PORT.print(" is ");
	if(_state)
		SERIAL_PORT.println("ON");
	else
		SERIAL_PORT.println("OFF");
}

/** printLedPinState()
 *  @brief Public method that prints the led pin state
 *  @param void 
 */
inline void LedBlinky::printLedPinState(void) const {
	SERIAL_PORT.print("Led pin ");
	SERIAL_PORT.print(_pin);
	SERIAL_PORT.print(" is ");
	if(_pinState)
		SERIAL_PORT.println("HIGH");
	else
		SERIAL_PORT.println("LOW");
}

/** printLedBrightness()
 *  @brief Public method that prints led brightness
 *  @param void 
 */
inline void LedBlinky::printLedBrightness(void) const {
	SERIAL_PORT.print("Led brightness is ");
	SERIAL_PORT.println(_brightness);
}

/**************************************** PUBLIC METHODS ****************************************/

/** printLedInfo()
 *  @brief Public method that prints all led info
 *  @param void 
 */
void LedBlinky::printLedInfo(void) const {
	printLedPinState();
	printLedState();
	printLedBrightness();
}

#endif

/** begin()
 *  @brief Public method that initializes the led.
 *         Usually this method is called in setup() function
 *  @param void
 */
void LedBlinky::begin(void) const {
	if(checkInit()) {
		pinMode(_pin, OUTPUT);
		digitalWrite(_pin, _pinState);
	}
#if defined(SERIAL_DEBUG)
	else {
		if(_pin == WRONG_PIN)
			SERIAL_PORT.println("Wrong pin number !");
		if(_state == WRONG_STATE)
			SERIAL_PORT.println("Wrong led state !");
	}
#endif
}

/** end()
 *  @brief Public method that disables the led pin
 *  @param void
 */
void LedBlinky::end(void) const {
	if(checkInit()) {
		digitalWrite(_pin, LOW);
		pinMode(_pin, INPUT);
#if defined(SERIAL_DEBUG)
		SERIAL_PORT.println("Led pin disabled");
		SERIAL_PORT.println("End Serial debug for Led library ...");
		SERIAL_PORT.end();
#endif
	}
}

/** on()
 *  @brief Public method that turns the led ON 
 *  @param void
 */
void LedBlinky::on(void) {
	setState(ON);
}

/** off()
 *  @brief Public method that turns the led OFF
 *  @param void
 */
void LedBlinky::off(void) {
	setState(OFF);
}

/** toggle()
 *  @brief Public method that change the led state, i.e
 *         if the led is ON, turn the led OFF
 *         else if the led is OFF, turn the led ON
 *  @param void
 */
void LedBlinky::toggle(void) {
	setState(1-_state);
}

/** setBrightness()
 *  @brief Public method that change the led brightness if the led pin
 *         is a PWM pin, otherwise it turns the led ON or OFF according
 *         to the value of brightness
 *  @param brightness used to set the led brightness
 */
void LedBlinky::setBrightness(uint8_t brightness) {
	if(checkInit()) {
		if(_pinPWM) {
			_brightness = brightness;
			if(_ledPullType == PULL_DOWN) {
				analogWrite(_pin, _brightness);
				
				if(_brightness) {
					_pinState = HIGH;
					_state = ON;
				}
				else {
					_pinState = LOW;
					_state = OFF;
				}
			}
			else {
				analogWrite(_pin, 255-_brightness);
				
				if(255-_brightness) {
					_pinState = HIGH;
					_state = ON;
				}
				else {
					_pinState = LOW;
					_state = OFF;
				}
			}
		#if defined(SERIAL_DEBUG)
			printLedBrightness();
		#endif
		}
		else {
			if(brightness)
				setState(ON);
			else
				setState(OFF);
		}
	}
}

/** blink()
 *  @brief Public method that turns the led ON setting the led brightness with the brightness
 *         parameter, waits for a delay time specified by onDelay, then turn the led OFF and
 *         finally waits for a delay time specified by offDelay.
 *         This method is used to blink a led
 *  @param onDelay : the amount of time the led is ON
 *  @param offDelay : the amount of time led is OFF
 *  @param brightness : used to set up the led brightness
 */
void LedBlinky::blink(long onDelay, long offDelay, uint8_t brightness) {
	setBrightness(brightness);
	delay(onDelay);
	setBrightness(0);
	delay(offDelay);
}

/** getLedState()
 *  @brief Public method that returns the led state
 *  @param void
 *  @return ON or OFF according to the led state
 */
bool LedBlinky::getState(void) const {
	if(_state)
		return ON;
	else
		return OFF;
}

/** getBrightness()
 *  @brief Public method that returns the led brightness 
 *  @param void
 *  @return the led brightness
 */
uint8_t LedBlinky::getBrightness(void) const {
	return _brightness;
}

/** getLedPinNumber()
 *  @brief Public method that returns the led pin number
 *  @param void
 *  @return the pin number to which the led is attached
 */
uint8_t LedBlinky::getLedPinNumber(void) const {
	return _pin;
}

/** getLedPinState()
 *  @brief Public method that returns the state of the pin
 *         to which the led is attached 
 *  @param void
 *  @return HIGH (1) or LOW (0) according to the pin state 
 */
bool LedBlinky::getLedPinState(void) const {
	return _pinState;
}

/** getLedPullType()
 *  @brief Public method used to know the led configuration
 *  @param void
 *  @return PULL_UP if the led uses a pull-up resistor, else
 *          PULL_DOWN if the led uses a pull-down resistor 
 */
PullType LedBlinky::getLedPullType(void) const {
	return _ledPullType;
}
