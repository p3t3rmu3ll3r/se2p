/*
 * Receiver.h
 *
 *  Created on: 24.11.2012
 *      Author: martin
 */

#ifndef RECEIVER_H_
#define RECEIVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/neutrino.h>

#include "Dispatcher.h"
#include "Mutex.h"
#include "RS232_1.h"
#include "address.h"

#define DEBUG_Receiver
#define B2_MSG0 0
#define B2_MSG1 1

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
	
	RS232_1* rs232_1;
};

#endif /* RECEIVER_H_ */
