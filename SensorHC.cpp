
#include "SensorHC.h"

SensorHC::SensorHC(int echoPin, int triggerPin)
{
    echoPin_ = echoPin;
    triggerPin_ = triggerPin;
	
}

long SensorHC::getDistance()
{
    return distance_;
}

void SensorHC::ping()
{
    digitalWrite(triggerPin_, LOW);
    delayMicroseconds(2);

    digitalWrite(triggerPin_, HIGH);
    delayMicroseconds(10);

    digitalWrite(triggerPin_, LOW);

    duration_ = pulseIn(echoPin_, HIGH);
    distance_ = duration_*0.034/2;
}

