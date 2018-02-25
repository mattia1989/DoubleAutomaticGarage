#include "ArduinoUtility.h"

/* PRIVATE SECTION */

ArduinoUtility::ArduinoUtility(const unsigned long pSerialDim)
{
	if (_ENABLE_SERIAL) Serial.begin(pSerialDim);
}

/* PUBLIC SECTION */

ArduinoUtility * ArduinoUtility::getInstance(const unsigned long pSerialDim)
{
	static ArduinoUtility * _myInstance = new ArduinoUtility(pSerialDim);

	return _myInstance;
}

void ArduinoUtility::println(String pLine)
{
	if (_ENABLE_SERIAL) Serial.println(pLine);
}


ArduinoUtility::~ArduinoUtility()
{
}
