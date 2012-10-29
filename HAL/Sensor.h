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


class Sensor {
public:
	Sensor();
	virtual ~Sensor();

	int getChid();
	int getCoid();

private:
	int chid;
	int coid;
	int interruptId;
	struct sigevent event;

	void initInterrupt();

};

#endif /* SENSOR_H_ */
