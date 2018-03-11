/*
 Name:		DoubleAutoGarage.ino
 Created:	06/02/2018 17:17:06
 Author:	Mattia Di Luca
*/

#include <Arduino.h>
#include <RCSwitch.h>

#include "SketchConstants.h"
#include "ArduinoUtility.h"
#include "AutomaticGarage.h"

// Global declaration
const bool MAIN_DEBUG = false;

RCSwitch* gRCSwitch = new RCSwitch();
AutomaticGarage* gGarageOnePtr = new AutomaticGarage(PIN_RELE_UP_1, PIN_RELE_DOWN_1, 
	PIN_SENSOR_UP_1, PIN_SENSOR_DOWN_2, CODE_UP_1, CODE_DOWN_1, HEIGHT_TIME_1);
AutomaticGarage* gGarageTwoPtr = new AutomaticGarage(PIN_RELE_UP_2, PIN_RELE_DOWN_2, 
	PIN_SENSOR_UP_2, PIN_SENSOR_DOWN_2, CODE_UP_2, CODE_DOWN_2, HEIGHT_TIME_2);

int gCode = 0;
unsigned long gDirection = 0;

// the setup function runs once when you press reset or power the board
void setup() {

	ArduinoUtility::getInstance()->println("Setup -> START");

	Serial.begin(9600);
	gRCSwitch->enableReceive(0);

	gGarageOnePtr->init();
	gGarageTwoPtr->init();

	ArduinoUtility::getInstance()->println("Setup -> END");
	
}

// the loop function runs over and over again until power down or reset
void loop() {

	if (MAIN_DEBUG) ArduinoUtility::getInstance()->println("Main loop -> START");

	// Get Value from Radio
	gCode = 0;

	if (gRCSwitch->available()) {
		gCode = gRCSwitch->getReceivedValue();
		gRCSwitch->resetAvailable();
	}

	// Get sensor's value of first garage TODO
	gDirection = 0;

	// TODO Read from sensor and set value
	gGarageOnePtr->sendValue(gCode);

	// Get sensor's value of second garage TODO
	gDirection = 0;

	// TODO Read from sensor and set value
	//gGarageTwoPtr->sendValue(gCode, gDirection);

	if (MAIN_DEBUG) ArduinoUtility::getInstance()->println("Main loop -> END");

}

