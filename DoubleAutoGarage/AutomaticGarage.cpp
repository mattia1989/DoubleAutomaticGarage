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

void AutomaticGarage::testSequence(const int pDelayTime)
{
	ArduinoUtility::getInstance()->println("testSequence(const int pDelayTime) -> START");

	this->_timerObjectPtr->Pause();
	Serial.print("Current timer -> ");
	Serial.println(this->_timerObjectPtr->getCurrentTime());

	this->up();
	delay(pDelayTime);
	this->down();
	delay(pDelayTime);
	this->stop();

	Serial.print("Is single shot -> ");
	Serial.println(this->_timerObjectPtr->isSingleShot());
	Serial.print("Is enable -> ");
	Serial.println(this->_timerObjectPtr->isEnabled());
	Serial.print("Get interval -> ");
	Serial.println(this->_timerObjectPtr->getInterval());
	Serial.print("Current timer -> ");
	Serial.println(this->_timerObjectPtr->getCurrentTime());

	this->_timerObjectPtr->Resume();
	Serial.print("Current timer -> ");
	Serial.println(this->_timerObjectPtr->getCurrentTime());
	
	ArduinoUtility::getInstance()->println("testSequence(const int pDelayTime) -> END");
}

/* PUBLIC SECTION */

AutomaticGarage::AutomaticGarage(const int pPinUp, const int pPinDown, const int pPinSensorUp, 
	const int pPinSensorDown, const int pCodeUp, const int pCodeDown, const unsigned long int 
	pDuration)
	
{
	this->setAutomaticGarage(pPinUp, pPinDown, pPinSensorUp, pPinSensorDown, 
		pCodeUp, pCodeDown, pDuration);
}

AutomaticGarage::~AutomaticGarage()
{
}

void AutomaticGarage::setPinUp(const int pPinUp)
{
	this->_pinUp = pPinUp;
}

void AutomaticGarage::setPinDow(const int pPinDown)
{
	this->_pinDown = pPinDown;
}

void AutomaticGarage::setPinSensorUp(const int pPinSensorUp)
{
	this->_pinSensorUp = pPinSensorUp;
}

void AutomaticGarage::setPinSensorDown(const int pPinSensorDown)
{
	this->_pinSensorDown = pPinSensorDown;
}

void AutomaticGarage::setGarageUpCode(const int pCodeUp)
{
	this->_garageUpCode = pCodeUp;
}

void AutomaticGarage::setGarageDownCode(const int pCodeDown)
{
	this->_garageDownCode = pCodeDown;
}

void AutomaticGarage::setStatus(const Status_garage status)
{
	this->_status = status;
}

void AutomaticGarage::setAutomaticGarage(const int pPinUp, const int pPinDown, 
	const int pPinSensorUp, const int pPinSensorDown, const int pCodeUp, const int 
	pCodeDown, const unsigned long int pDuration)
{
	this->setPinUp(pPinUp);
	this->setPinDow(pPinDown);
	this->setPinSensorUp(pPinSensorUp);
	this->setPinSensorDown(pPinSensorDown);
	this->setGarageUpCode(pCodeUp);
	this->setGarageDownCode(pCodeDown);
	this->setStatus(INITIAL);

	this->_timerObjectPtr = new TimerObject(pDuration);
}

void AutomaticGarage::init()
{
	// Initialize all pins
	this->initRele();
	this->initSensor();

	// Complete initialization of timer
	this->_timerObjectPtr->setSingleShot(AutomaticGarage::IS_SINGLE_SHOT);


	/////////////////////////////////////////////////////////////////////

	this->_timerObjectPtr->setOnTimer(this);

	/////////////////////////////////////////////////////////////////////

}

void AutomaticGarage::initRele()
{
	// Initialize all reles' pins
	pinMode(this->_pinUp, OUTPUT);
	pinMode(this->_pinDown, OUTPUT);
}

void AutomaticGarage::initSensor()
{
	// Initialize all sensors' pins
	pinMode(this->_pinSensorUp, INPUT);
	pinMode(this->_pinSensorDown, INPUT);
}

void AutomaticGarage::sendValue(unsigned long pCode, unsigned long pDirectionSensor)
{
	// Update timer
	this->_timerObjectPtr->Update();
	Serial.print("Current timer -> ");
	Serial.println(this->_timerObjectPtr->getCurrentTime());

	// Check signal
	if (pCode == this->_garageUpCode)
	{
		// TODO Implement the algoritm
		if (this->_status == Status_garage::INITIAL)
		{
			this->_status = Status_garage::UP;
			this->_timerObjectPtr->Start();
			this->up();
		}
		else if (this->_status == Status_garage::UP)
		{
			this->stop();
			this->_timerObjectPtr->Pause();
			this->_status = Status_garage::PAUSE;
		}
		else if (this->_status == Status_garage::PAUSE)
		{
			this->up();
			this->_timerObjectPtr->Resume();
			this->_status = Status_garage::UP;
		}
		else if (this->_status == Status_garage::FINISH)
		{
			this->up();
			delay(1000);
			this->stop();
			this->_status = Status_garage::OVER_UP;
		}
		else if (this->_status == Status_garage::OVER_UP)
		{
			this->down();
			delay(1000);
			this->setStatus(Status_garage::DOWN);
			this->_timerObjectPtr->Start();
		}
	}

}

void AutomaticGarage::sendValue(unsigned long pCode)
{
	this->sendValue(pCode, this->SENSOR_DIRECTION_NONE);
}

/* CALLBACK & LISTENER SECTION */

void AutomaticGarage::onTimeExpiriedCallback()
{
	ArduinoUtility::getInstance()->println("onTimeExpiriedCallback -> START");

	// TODO Implement it correctly
	if (this->_status == Status_garage::UP)
	{
		this->stop();
		this->_status = Status_garage::FINISH;
	}
	else if (this->_status == Status_garage::DOWN)
	{
		this->stop();
		this->_status = Status_garage::INITIAL;
	}

	ArduinoUtility::getInstance()->println("onTimeExpiriedCallback -> END");
}

