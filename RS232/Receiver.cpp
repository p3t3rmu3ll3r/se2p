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
	rs232_1 = RS232_1::getInstance();
	
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
	char buffer = '0';
	int readBytes; 
	int rc;
	int pulseval = -1;
	
	while (!isStopped()) {
		readBytes = rs232_1->readMsg(&buffer);

		if (readBytes < 0) {
			printf("Error Receiver: Error in readMsg\n");
		}

		if (readBytes > 0) {

			switch (buffer) {
			case '0':
				pulseval = B2_MSG0;
#ifdef DEBUG_Receiver
				printf("Received random shit to be defined\n");
#endif
				break;
			case '1':
				pulseval = B2_MSG1;
#ifdef DEBUG_Receiver
				printf("Received random shit to be defined\n");
#endif
				break;
			default:
#ifdef DEBUG_Receiver
				printf("Received random shit to be defined\n");
#endif
			}
			rc = MsgSendPulse(coid, SIGEV_PULSE_PRIO_INHERIT, PULSE_FROM_RS232, pulseval);
			if (rc < 0) {
				printf("Error Receiver: MsgSendPulse failed\n");
			}

		}
		
		fflush(stdout);
	};
}

void Receiver::shutdown() {
}
