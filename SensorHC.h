#ifndef SENSORHC_H_
#define SENSORHC_H_

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <inttypes.h>

class SensorHC {

public:
	SensorHC(int echoPin, int triggerPin);

	long getDistance();

	void ping();

private:

	int echoPin_, triggerPin_;
	long duration_, distance_;
};
#endif
