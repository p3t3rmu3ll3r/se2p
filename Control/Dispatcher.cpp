/*
 * Dispatcher.cpp
 *
 *  Created on: 17.11.2012
 *      Author: martin
 */

#include "Dispatcher.h"

Dispatcher* Dispatcher::instance = NULL;
Mutex* Dispatcher::dispatcherInstanceMutex = new Mutex();

Dispatcher::Dispatcher() {
	//Create channel for pulse notification
	if ((chid = ChannelCreate(0)) == -1) {
		printf("Dispatcher: Error in ChannelCreate\n");
	}

	//Connect to channel
	if ((coid = ConnectAttach(0, 0, chid, _NTO_SIDE_CHANNEL, 0)) == -1) {
		printf("Dispatcher: Error in ConnectAttach\n");
	}
}

Dispatcher::~Dispatcher() {
	if (instance != NULL) {
		delete instance;
		instance = NULL;
		dispatcherInstanceMutex->~Mutex();
	}
}

Dispatcher* Dispatcher::getInstance() {
	if (!instance) {
		dispatcherInstanceMutex->lock();
		if (!instance) {
			instance = new Dispatcher;
#ifdef DEBUG_DISPATCHER
			printf("Debug Dispatcher: New Dispatcher instance created\n");
#endif
		}
		dispatcherInstanceMutex->unlock();
	}

	return instance;
}

//TODO register4IRQ und unregister4IRQ implementen, call interface aus enum in messages bauen
void Dispatcher::execute(void*) {
	int rc;
	struct _pulse pulse;

	while(!isStopped()){
		//TODO wenn man auf einem channel mit 2 threads lauscht und thread1 bekommt den pulse zuerst, erhält thread2 ihn trotzdem oder nur einer von beiden?
		//TODO beide automaten mit gleichen funktionen auf das callinterface?!
		//TODO sollen die knoepfe schon ins ms4 funzen?
		//TODO soll die COM schon mit band2 funzen und auf beiden gefahren werden?
		rc = MsgReceivePulse(chid, &pulse, sizeof(pulse), NULL);
		if (rc < 0) {
			printf("Dispatcher: Error in recv pulse\n");
			if (isStopped()) {
				break;
			}
		}
		//TODO do time consuming stuff...

		if(pulse.code == PULSE_FROM_ISRHANDLER){
			//werte pulseval aus
			//TODO forward all regged puks the msg (set *fp actually)
		}
	}
}

void Dispatcher::stop() {
	HAWThread::stop();

	if (ConnectDetach(coid) == -1) {
		printf("Dispatcher: Error in ConnectDetach\n");
	}

	if (ChannelDestroy(chid) == -1) {
		printf("Dispatcher: Error in ChannelDestroy\n");
	}
}

void Dispatcher::shutdown() {
}

int Dispatcher::getChid() {
	return chid;
}
