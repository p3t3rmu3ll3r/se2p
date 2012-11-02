/*
 * ISRTest.h
 *
 *  Created on: 29.10.2012
 *      Author: martin
 */

#ifndef ISRTEST_H_
#define ISRTEST_H_

#include "HAWThread.h"
#include "address.h"
#include "SensorHAL.h"
#include "ActorHAL.h"

class ISRTest : public thread::HAWThread {
public:
	ISRTest();
	virtual ~ISRTest();

	virtual void execute(void* arg);
	virtual void shutdown();
	//TODO stop methode ueberschreiben, stop von hawthread ausfuehren,
	//danach stopInterrupt aus SensorHAl aufrufen. Wichtig fuer unseren Dispatcher
	//der wird spaeter im MsgReceivePulse blocken
};

#endif /* ISRTEST_H_ */
