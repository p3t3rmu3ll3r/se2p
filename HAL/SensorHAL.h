/*
 * Sensor.h
 *
 *  Created on: 28.10.2012
 *      Author: martin
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#include <stdlib.h>

#include "address.h"
#include "HWaccess.h"
#include "sys/siginfo.h"
#include "Mutex.h"
#include <iostream>

#define DEBUG_SENSORHAL

class SensorHAL {
public:
	virtual ~SensorHAL();

	static SensorHAL* getInstance();
	int getChid();
	int getCoid();
	int getHeight();
	void stopInterrupt();

private:
	SensorHAL();
	void initInterrupt();

	int chid;
	int coid;
	int interruptId;
	struct sigevent event;
	static SensorHAL* instance;
	static Mutex* sensorInstanceMutex;


};

#endif /* SENSOR_H_ */
