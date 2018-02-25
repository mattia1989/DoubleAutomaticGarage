#pragma once

#ifndef __ARDUINO_UTITLIY_H__
#define __ARDUINO_UTILITY_H__

#define _PORTAL_DIMENSION 9600
#define _ENABLE_SERIAL 1

#include <Arduino.h>

class ArduinoUtility
{
private:
	ArduinoUtility(const unsigned long pSerialDim = _PORTAL_DIMENSION);
	ArduinoUtility(const ArduinoUtility &);
	void operator=(const ArduinoUtility &);

public:
	static ArduinoUtility * getInstance(unsigned long pSerialDim = _PORTAL_DIMENSION);

	void println(String pLine);

	~ArduinoUtility();

};

#endif // !__ARDUINO_UTITLIY_H__

