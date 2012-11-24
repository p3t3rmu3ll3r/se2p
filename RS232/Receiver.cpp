/*
 * Receiver.cpp
 *
 *  Created on: 24.11.2012
 *      Author: martin
 */

#include "Receiver.h"

Receiver* Receiver::instance = NULL;
Mutex* Receiver::receiverInstanceMutex = new Mutex();

Receiver::Receiver() {
	disp = Dispatcher::getInstance();
	dispatcherChid = disp->getChid();

	//Connect to channel
	if ((coid = ConnectAttach(0, 0, dispatcherChid, _NTO_SIDE_CHANNEL, 0))
			== -1) {
		printf("Receiver: Error in ConnectAttach\n");
	}
}

Receiver::~Receiver() {
	if (instance != NULL) {
		delete instance;
		instance = NULL;
		receiverInstanceMutex->~Mutex();
	}
}

Receiver* Receiver::getInstance() {
	if (!instance) {
		receiverInstanceMutex->lock();
		if (!instance) {
			instance = new Receiver;
#ifdef DEBUG_Receiver
			printf("Debug Receiver: New Receiver instance created\n");
#endif
		}
		receiverInstanceMutex->unlock();
	}

	return instance;
}

void Receiver::execute(void*) {
}

void Receiver::shutdown() {
}
