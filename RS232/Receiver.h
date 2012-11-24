/*
 * Receiver.h
 *
 *  Created on: 24.11.2012
 *      Author: martin
 */

#ifndef RECEIVER_H_
#define RECEIVER_H_

#include "Dispatcher.h"
#include "Mutex.h"

#define DEBUG_Receiver

class Receiver: public thread::HAWThread {
public:
	virtual void execute(void* arg);
	virtual void shutdown();
	static Receiver* getInstance();
	virtual ~Receiver();

private:
	Receiver();

	static Receiver* instance;
	static Mutex* receiverInstanceMutex;
	Dispatcher* disp;
	int dispatcherChid;
	int coid;
};

#endif /* RECEIVER_H_ */
