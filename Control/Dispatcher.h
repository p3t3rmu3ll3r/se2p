/*
 * Dispatcher.h
 *
 *  Created on: 17.11.2012
 *      Author: martin
 */

#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include <vector>
#include <stdint.h>
#include "HAWThread.h"
#include "HWaccess.h"
#include "messages.h"
#include "address.h"
#include "Mutex.h"
#include "CallInterface.h"
#include "LightController.h"


#define DEBUG_DISPATCHER

typedef void (CallInterface::*callFuncs)();

class Dispatcher: public thread::HAWThread {
public:
	static Dispatcher* getInstance();
	virtual void execute(void* arg);
	virtual void shutdown();
	void stop();
	virtual ~Dispatcher();

	void registerContextForFunc(int funcIdx, CallInterface* context);
	void registerContextForAllFuncs(CallInterface* context);

	int getChid();
	int getStopChid();
	void setEstop(bool eStop);

private:
	Dispatcher();

	static Dispatcher* instance;
	static Mutex* dispatcherInstanceMutex;
	int chid;
	int coid;
	int stopChid;
	int stopCoid;
	bool eStop;

	callFuncs* funcArr;
	LightController* lc;
	vector<CallInterface*> controllersForFunc[MESSAGES_SIZE];
};

#endif /* DISPATCHER_H_ */
