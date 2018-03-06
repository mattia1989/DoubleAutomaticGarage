
#ifndef __AUTOMATICGARAGE_H__
#define __AUTOMATICGARAGE_H__

#include <Arduino.h>

#include "ArduinoUtility.h"
#include "TimerObject.h"
#include "StatusGarage.h"

#define _MANUAL_DELAY_ 1000
#define _DEFAULT_DURATION_ 5000
#define _DEFAULT_OVER_DURATION_ 10000
#define _MAX_OVER_TIME_ 3100

class AutomaticGarage
{
private:
	// Sensor
	const static int SENSOR_DIRECTION_UP = 1;
	const static int SENSOR_DIRECTION_DOWN = -1;
	const static int SENSOR_DIRECTION_NONE = 0;

	// Tipe of run of TimerObject
	const static bool IS_SINGLE_SHOT = true;

	// Pins
	const int _pinUp;
	const int _pinDown;
	const int _pinSensorUp;
	const int _pinSensorDown;

	// Command codes
	const int _garageUpCode;
	const int _garageDownCode;

	// Tracer
	Status_garage _status;
	TimerObject* _standardTimerPtr;
	TimerObject* _overTimerPtr;

	void up();
	void down();
	void stop();

	void autoOverUp();
	void autoOverDown();

	void updateTimer();

public:
	AutomaticGarage(const int pPinUp, const int pPinDown, const int pPinSensorUp,
		const int pPinSensorDown, const int pCodeUp, const int pCodeDown);
	AutomaticGarage(const int pPinUp, const int pPinDown, const int pPinSensorUp, 
		const int pPinSensorDown, const int pCodeUp, const int pCodeDown, const 
		unsigned long int pDuration);
	~AutomaticGarage();

	void setStatus(const Status_garage);

	/* GETTER */
	const int getPinUp();
	const int getPinDow();
	const int getPinSensorUp();
	const int getPinSensorDown();
	const int getGarageUpCode();
	const int getGarageDownCode();
	const Status_garage getStatus();
	TimerObject* getStandardTimerPtr();
	TimerObject* getOverTimerPtr();

	bool checkStatus(Status_garage pStatus);

	const AutomaticGarage * getAutomaticGarage();
	
	/* INITIALIZER */
	void init();
	void initRele();
	void initSensor();
	void initStatus();
	void initTimer();

	void testSequence(const int pDelayTime);

	/* SENDER */
	void sendValue(unsigned long pCode);
	void sendValue(unsigned long pCode, unsigned long pDirectionSensor);

	/* CALLBACKER*/
	void onTimeExpiriedCallback();

};

#endif // !__AUTOMATICGARAGE_H__

