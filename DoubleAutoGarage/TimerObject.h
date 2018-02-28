#include "stdlib.h"
#include "Arduino.h"

#ifndef TIMER_OBJECT_H
#define TIMER_OBJECT_H

#include "AutomaticGarage.h"

class TimerObject {
private:

	void Create(unsigned long int ms, AutomaticGarage * callback, bool isSingle);
	unsigned long int msInterval;
	bool blEnabled;
	bool blSingleShot;
	AutomaticGarage * onRun;
	bool Tick();
	unsigned long LastTime;
	unsigned long DiffTime;//used when I pause the Timer and need to resume

public:
	TimerObject(unsigned long int ms);
	TimerObject(unsigned long int ms, AutomaticGarage * callback);
	TimerObject(unsigned long int ms, AutomaticGarage * callback, bool isSingle);
	~TimerObject();

	void setInterval(unsigned long int ms);
	void setEnabled(bool Enabled);
	void setSingleShot(bool isSingle);
	void setOnTimer(AutomaticGarage * callback);
	void Start();
	void Resume();
	void Pause();
	void Stop();
	void Update();
	
	unsigned long int getInterval();
	unsigned long int getCurrentTime();
	AutomaticGarage * getOnTimerCallback();

	bool isEnabled();
	bool isSingleShot();

};


#endif // TIMER_OBJECT_H
