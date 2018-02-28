#pragma once

#ifndef __AUTOMATICGARAGE_H__
#define __AUTOMATICGARAGE_H__

#include <Arduino.h>

#include "ArduinoUtility.h"
#include "TimerObject.h"
#include "StatusGarage.h"

#define MANUAL_DELAY 1000

class AutomaticGarage
{
private:
	// Sensor
	const int SENSOR_DIRECTION_UP = 1;
	const int SENSOR_DIRECTION_DOWN = -1;
	const int SENSOR_DIRECTION_NONE = 0;

	// Tipe of run of TimerObject
	const bool IS_SINGLE_SHOT = true;

	// Command codes
	unsigned long _garageUpCode;
	unsigned long _garageDownCode;

	Status_garage _status;

	// Tracer of height
	TimerObject* _timerObjectPtr;

	// Pins
	int _pinUp;
	int _pinDown;
	int _pinSensorUp;
	int _pinSensorDown;

	void up();
	void down();
	void stop();

public:
	AutomaticGarage(const int pPinUp, const int pPinDown, const int pPinSensorUp,
		const int pPinSensorDown, const unsigned long pCodeUp, const unsigned long
		pCodeDown, const unsigned long int pDuration);
	~AutomaticGarage();

	void setPinUp(const int pPinUp);
	void setPinDow(const int pPinDown);
	void setPinSensorUp(const int pPinSensorUp);
	void setPinSensorDown(const int pPinSensorDown);
	void setGarageUpCode(const unsigned long pCodeUp);
	void setGarageDownCode(const unsigned long pCodeDown);
	void setStatus(const Status_garage);

	void setAutomaticGarage(const int pPinUp, const int pPinDown, const int pPinSensorUp,
		const int pPinSensorDown, const unsigned long pCodeUp, const unsigned long pCodeDown,
		const unsigned long int pDuration);
	
	void init();
	void initRele();
	void initSensor();
	void testSequence(const int pDelayTime);

	void sendValue(unsigned long pCode, unsigned long pDirectionSensor);
	void sendValue(unsigned long pCode);

	void onTimeExpiriedCallback();

};

#endif // !__AUTOMATICGARAGE_H__

