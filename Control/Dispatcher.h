/*
 * Dispatcher.h
 *
 *  Created on: 17.11.2012
 *      Author: martin
 */

#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include "HAWThread.h"
#include "HWaccess.h"
#include "messages.h"
#include "address.h"
#include "Mutex.h"

#define DEBUG_DISPATCHER

class Dispatcher: public thread::HAWThread {
public:
	int getChid();
	static Dispatcher* getInstance();

	virtual void execute(void* arg);
	virtual void shutdown();
	void stop();
	virtual ~Dispatcher();

private:
	Dispatcher();

	static Dispatcher* instance;
	static Mutex* dispatcherInstanceMutex;
	int chid;
	int coid;
};

#endif /* DISPATCHER_H_ */
