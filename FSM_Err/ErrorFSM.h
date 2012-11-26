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

class ErrorFSM: public thread::HAWThread {
public:
	ErrorFSM();
	virtual ~ErrorFSM();
	virtual void execute(void* arg);
	virtual void shutdown();
	void stop();
	int getErrorFSMChid();
	int getReplyChid();

private:
	int ownChid;
	int replyChid;
	int replyCoid;
	int state;
	ActorHAL* aHal;
	LightController* lc;

	void sendPuckReply();
};

#endif /* ERRORFSM_H_ */
