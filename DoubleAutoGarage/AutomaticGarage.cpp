#include "StatusGarage.h"
#include "AutomaticGarage.h"

/* PRIVATE SECTION */

void AutomaticGarage::up()
{
	ArduinoUtility::getInstance()->println("call method up()");
	digitalWrite(this->_pinUp, HIGH);  // Open Rele up
}

void AutomaticGarage::down()
{
	ArduinoUtility::getInstance()->println("call method down()");
	digitalWrite(this->_pinDown, HIGH);  // Open Rele down
}

void AutomaticGarage::stop()
{
	ArduinoUtility::getInstance()->println("call method stop()");
	digitalWrite(this->_pinUp, LOW);  // Close Rele up
	digitalWrite(this->_pinDown, LOW);  // Close Rele down
}

void AutomaticGarage::autoOverUp()
{
	this->up();
	delay(_MANUAL_DELAY_);
	this->stop();
}

void AutomaticGarage::autoOverDown()
{
	this->down();
	delay(_MANUAL_DELAY_);
	this->stop();
}

void AutomaticGarage::updateTimer()
{
	this->getStandardTimerPtr()->Update();
	this->getOverTimerPtr()->Update();
}

void AutomaticGarage::testSequence(const int pDelayTime)
{
	ArduinoUtility::getInstance()->println("testSequence(const int pDelayTime) -> START");

	this->_standardTimerPtr->Pause();
	Serial.print("Current timer -> ");
	Serial.println(this->_standardTimerPtr->getCurrentTime());

	this->up();
	delay(pDelayTime);
	this->down();
	delay(pDelayTime);
	this->stop();

	Serial.print("Is single shot -> ");
	Serial.println(this->_standardTimerPtr->isSingleShot());
	Serial.print("Is enable -> ");
	Serial.println(this->_standardTimerPtr->isEnabled());
	Serial.print("Get interval -> ");
	Serial.println(this->_standardTimerPtr->getInterval());
	Serial.print("Current timer -> ");
	Serial.println(this->_standardTimerPtr->getCurrentTime());

	this->_standardTimerPtr->Resume();
	Serial.print("Current timer -> ");
	Serial.println(this->_standardTimerPtr->getCurrentTime());
	
	ArduinoUtility::getInstance()->println("testSequence(const int pDelayTime) -> END");
}

/* PUBLIC SECTION */

AutomaticGarage::AutomaticGarage(const int pPinUp, const int pPinDown, const int pPinSensorUp, const int pPinSensorDown, const int pCodeUp, const int pCodeDown)
{
	AutomaticGarage(pPinUp, pPinDown, pPinSensorUp, pPinSensorDown, pCodeUp,
		pCodeDown, _DEFAULT_DURATION_);
}

AutomaticGarage::AutomaticGarage(const int pPinUp, const int pPinDown, const int pPinSensorUp,
	const int pPinSensorDown, const int pCodeUp, const int pCodeDown, const unsigned long int 
	pDuration):_pinUp(pPinUp), _pinDown(pPinDown), _pinSensorUp(pPinSensorUp), 
	_pinSensorDown(pPinSensorDown), _garageUpCode(pCodeUp), _garageDownCode(pCodeDown)
{
	this->_standardTimerPtr = new TimerObject(pDuration);
	this->_overTimerPtr = new TimerObject(_DEFAULT_OVER_DURATION_);
}

AutomaticGarage::~AutomaticGarage()
{
}

void AutomaticGarage::setStatus(const Status_garage status)
{
	this->_status = status;
}

void AutomaticGarage::init()
{
	// Initialize all pins
	this->initRele();
	this->initSensor();

	// Init tracer
	this->initStatus();
	this->initTimer();

}

void AutomaticGarage::initRele()
{
	// Initialize all reles' pins
	pinMode(this->_pinUp, OUTPUT);
	pinMode(this->_pinDown, OUTPUT);
}

void AutomaticGarage::initSensor()
{
	// Initialize all sensors'pins
	pinMode(this->_pinSensorUp, INPUT);
	pinMode(this->_pinSensorDown, INPUT);
}

void AutomaticGarage::initStatus()
{
	this->setStatus(Status_garage::INITIAL);
}

void AutomaticGarage::initTimer()
{
	this->getStandardTimerPtr()->setSingleShot(AutomaticGarage::IS_SINGLE_SHOT);
	this->getStandardTimerPtr()->setOnTimer(this);

	//this->_timerOverTimerPtr->
}

const int AutomaticGarage::getPinUp()
{
	return this->_pinUp;
}

const int AutomaticGarage::getPinDow()
{
	return this->_pinDown;
}

const int AutomaticGarage::getPinSensorUp()
{
	return this->_pinSensorUp;
}

const int AutomaticGarage::getPinSensorDown()
{
	return this->_pinSensorDown;
}

const int AutomaticGarage::getGarageUpCode()
{
	return this->_garageUpCode;
}

const int AutomaticGarage::getGarageDownCode()
{
	return this->_garageDownCode;
}

const Status_garage AutomaticGarage::getStatus()
{
	return this->_status;
}

TimerObject * AutomaticGarage::getStandardTimerPtr()
{
	return this->_standardTimerPtr;
}

TimerObject * AutomaticGarage::getOverTimerPtr()
{
	return this->_overTimerPtr;
}

bool AutomaticGarage::checkStatus(Status_garage pStatus)
{
	bool _return = false;

	if (this->getStatus() == pStatus) { _return = true; }

	return _return;
}

const AutomaticGarage * AutomaticGarage::getAutomaticGarage()
{
	return this;
}

void AutomaticGarage::sendValue(unsigned long pCode, unsigned long pDirectionSensor)
{
	// Update timer
	this->updateTimer();
	Serial.print("Current Standrd timer -> ");
	Serial.println(this->getStandardTimerPtr()->getCurrentTime());
	Serial.print("Current Over timer -> ");
	Serial.println(this->getOverTimerPtr()->getCurrentTime());

	// Check
	if (this->checkStatus(Status_garage::INITIAL))
	{
		if (pDirectionSensor == AutomaticGarage::SENSOR_DIRECTION_NONE)
		{
			if (pCode == this->getGarageUpCode())
			{
				// Start up
				this->up();
				this->getStandardTimerPtr()->Start();
				this->setStatus(Status_garage::UP);
			}
			else if (pCode == this->getGarageDownCode())
			{
				
			}
			else
			{
				// No code && No signal && initial -> nothing
			}
		}
		else if (pDirectionSensor == AutomaticGarage::SENSOR_DIRECTION_UP)
		{
			// Trace up
			this->getStandardTimerPtr()->Start();
			this->setStatus(Status_garage::MANUAL_UP);
		}
		else if (pDirectionSensor == AutomaticGarage::SENSOR_DIRECTION_DOWN)
		{
		}
	}
	else if (this->checkStatus(Status_garage::UP))
	{
		/* The following status is inconcistency because if the status is up, the */
		/*                       direction sensor can not be none                 */

		if (pDirectionSensor == AutomaticGarage::SENSOR_DIRECTION_NONE)
		{
			if (pCode == this->getGarageUpCode())
			{
				// Inconcistent -> raise exception
			}
			else if (pCode == this->getGarageDownCode())
			{
				// Inconcistent -> raise exception
			}
			else
			{
				// Inconcistent -> raise exception
			}
		}
		else if (pDirectionSensor == AutomaticGarage::SENSOR_DIRECTION_UP)
		{
			if ((pCode == this->getGarageUpCode()) || (pCode == this->getGarageDownCode()))
			{
				// Set in pause
				this->stop();
				this->getStandardTimerPtr()->Pause();
				this->setStatus(Status_garage::PAUSE);
			}
			else
			{
				// Do nothing
			}
		}
		else if (pDirectionSensor == AutomaticGarage::SENSOR_DIRECTION_DOWN)
		{
			if (pCode == this->getGarageUpCode())
			{
				
			}
			else if (pCode == this->getGarageDownCode())
			{
				
			}
			else
			{

			}

		}
	}
	else if (this->checkStatus(Status_garage::MANUAL_UP))
	{
		if (pDirectionSensor == AutomaticGarage::SENSOR_DIRECTION_NONE)
		{
			if (pCode == this->getGarageUpCode())
			{

			}
			else if (pCode == this->getGarageDownCode())
			{

			}
			else
			{

			}
		}
		else if (pDirectionSensor == AutomaticGarage::SENSOR_DIRECTION_UP)
		{
			if (pCode == this->getGarageUpCode())
			{

			}
			else if (pCode == this->getGarageDownCode())
			{

			}
			else
			{

			}
		}
		else if (pDirectionSensor == AutomaticGarage::SENSOR_DIRECTION_DOWN)
		{
			if (pCode == this->getGarageUpCode())
			{

			}
			else if (pCode == this->getGarageDownCode())
			{

			}
			else
			{

			}

		}
	}
	// ELSE IF --> TODO Implement the next state
}

void AutomaticGarage::sendValue(unsigned long pCode)
{
	this->sendValue(pCode, this->SENSOR_DIRECTION_NONE);
}

/* CALLBACK SECTION */

void AutomaticGarage::onTimeExpiriedCallback()
{
	ArduinoUtility::getInstance()->println("onTimeExpiriedCallback -> START");

	// Implement it correctly
	this->getStandardTimerPtr()->Stop();

	if (this->checkStatus(Status_garage::UP) || this->checkStatus(Status_garage::MANUAL_UP))
	{
		this->_status = Status_garage::FINISH;
	}
	else if (this->checkStatus(Status_garage::DOWN) || this->checkStatus(Status_garage::MANUAL_DOWN))
	{
		delay(_MANUAL_DELAY_);
		this->_status = Status_garage::INITIAL;
	}

	this->stop();

	ArduinoUtility::getInstance()->println("onTimeExpiriedCallback -> END");
}

