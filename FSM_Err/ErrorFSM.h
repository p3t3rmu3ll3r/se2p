/*
 * ErrorFSM.h
 *
 *  Created on: 26.11.2012
 *      Author: martin
 */

#ifndef ERRORFSM_H_
#define ERRORFSM_H_

#include "sys/neutrino.h"
#include "address.h"
#include "HAWThread.h"
#include "messages.h"
#include "errorStates.h"
#include "ActorHAL.h"
#include "LightController.h"
#include "Mutex.h"
#include "Dispatcher.h"
#include "PuckHandler.h"

#define DEBUG_ErrorFSM
class ErrorFSM: public thread::HAWThread {
public:
	virtual ~ErrorFSM();
	static ErrorFSM* getInstance();
	virtual void execute(void* arg);
	virtual void shutdown();
	void stop();
	int getErrorFSMChid();
	int getReplyChid();

private:
	ErrorFSM();
	int ownChid;
	int replyChid;
	int replyCoid;

	static ErrorFSM* instance;
	static Mutex* errfsmInstanceMutex;

	int state;
	int oldState;
	ActorHAL* aHal;
	Dispatcher* disp;
	LightController* lc;

	void sendPuckReply();
};

#endif /* ERRORFSM_H_ */
