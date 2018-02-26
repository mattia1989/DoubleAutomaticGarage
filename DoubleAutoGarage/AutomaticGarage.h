
#ifndef __AUTOMATICGARAGE_H__
#define __AUTOMATICGARAGE_H__

#include <Arduino.h>

#include "ArduinoUtility.h"
#include "TimerObject.h"

#define MANUAL_DELAY 1000

class AutomaticGarage
{
private:
	// Sensor
	const int SENSOR_DIRECTION_UP = 1;
	const int SENSOR_DIRECTION_DOWN = -1;
	const int SENSOR_DIRECTION_NONE = 0;

	// Number of run of timer
	const bool IS_SINGLE_SHOT = true;

	// Command codes
	unsigned long _garageUpCode;
	unsigned long _garageDownCode;

	// Enumeration for Garage Status
	enum Status_garage
	{
		INITIAL = 0,
		UP = 1,
		DOWN = -1,
		PAUSE = 2,
		MANUAL = -2,
		FINISH = 3,
		OVER_UP = -3,
		OVER_DOWN = 4
	};
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

	void sendValue(unsigned long pCode, Status_garage pDirectionSensor);
	void sendValue(unsigned long pCode);

	void onTimeExpiriedCallback();

};

#endif // !__AUTOMATICGARAGE_H__

