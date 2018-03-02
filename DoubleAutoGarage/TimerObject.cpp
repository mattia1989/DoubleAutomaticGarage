#include "AutomaticGarage.h"

TimerObject::TimerObject(unsigned long int ms) {
	Create(ms, NULL, false);
}

TimerObject::TimerObject(unsigned long int ms, AutomaticGarage * callback) {
	Create(ms, callback, false);
}

TimerObject::TimerObject(unsigned long int ms, AutomaticGarage * callback, bool isSingle) {
	Create(ms, callback, isSingle);
}

/* PRIVATE METHODS */

void TimerObject::Create(unsigned long int ms, AutomaticGarage * callback, bool isSingle) {
	setInterval(ms);
	setEnabled(false);
	setSingleShot(isSingle);
	setOnTimer(callback);
	LastTime = 0;
}

bool TimerObject::Tick() {
	if (!blEnabled)
		return false;
	if (LastTime > millis() * 2)//millis restarted
		LastTime = 0;
	if ((unsigned long int)(millis() - LastTime) >= msInterval) {
		LastTime = millis();
		if (isSingleShot())
			setEnabled(false);
		return true;
	}
	return false;
}

/* PUBLIC METHODS */

void TimerObject::setInterval(unsigned long int ms) {
	msInterval = (ms > 0) ? ms : 0;
}

void TimerObject::setEnabled(bool Enabled) {
	blEnabled = Enabled;
}

void TimerObject::setSingleShot(bool isSingle) {
	blSingleShot = isSingle;
}

void TimerObject::setOnTimer(AutomaticGarage * callback) {
	onRun = callback;
}

void TimerObject::Start() {
	LastTime = millis();
	setEnabled(true);
}

void TimerObject::Resume() {
	LastTime = millis() - DiffTime;
	setEnabled(true);
}

void TimerObject::Stop() {
	setEnabled(false);

}

void TimerObject::Pause() {
	DiffTime = millis() - LastTime;
	setEnabled(false);

}

void TimerObject::Update() {
	if (Tick())
		onRun->onTimeExpiriedCallback();
}

unsigned long int TimerObject::getInterval() {
	return msInterval;
}

unsigned long int TimerObject::getCurrentTime() {
	return (unsigned long int)(millis() - LastTime);
}
AutomaticGarage * TimerObject::getOnTimerCallback() {
	return onRun;
}

bool TimerObject::isEnabled() {
	return blEnabled;
}

bool TimerObject::isSingleShot() {
	return blSingleShot;
}

