/**
 * SE2 WiSe 2012
 * ISR with pulse messages
 *
 *
 * \file ISRHandler.h
 * \author Chris Addo
 *         Jens Eberwein
 *         Tristan Rudat
 *         Martin Slowikowski
 * \date 2012-11-17
 * \version 0.1
 *
 */

#ifndef ISRHANDLER_H_
#define ISRHANDLER_H_

#include "HAWThread.h"
#include "address.h"
#include "SensorHAL.h"
#include "messages.h"
#include "Mutex.h"
#include "Dispatcher.h"

#define DEBUG_ISRHandler

class ISRHandler: public thread::HAWThread {
public:
	//TODO singeltoen
	virtual ~ISRHandler();
	static ISRHandler* getInstance();
	virtual void execute(void* arg);
	virtual void shutdown();
	void stop();
	//TODO stop methode ueberschreiben, stop von hawthread ausfuehren,
	//danach stopInterrupt aus SensorHAl aufrufen. Wichtig fuer unseren Dispatcher
	//der wird spaeter im MsgReceivePulse blocken. alternativ immer IRQs gesondert
	//abschalten, solange kein anderer dispatcher/thread die msges verarbeitet
	//kann das aber stop mitmachen.

private:
	ISRHandler();

	static ISRHandler* instance;
	static Mutex* isrhandlerInstanceMutex;
	SensorHAL* sHal;
	Dispatcher* disp;
	int dispatcherChid;
	int coid;
};

#endif /* ISRHANDLER_H_ */
