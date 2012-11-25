/*
 * Dispatcher.cpp
 *
 *  Created on: 17.11.2012
 *      Author: martin
 */

#include "PuckHandler.h"

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

	funcArr = new callFuncs[MESSAGES_SIZE];
	int i = 0;

	funcArr[i++] = &CallInterface::sbStartOpen;
	funcArr[i++] = &CallInterface::sbStartClosed;
	funcArr[i++] = &CallInterface::sbHeightcontrolOpen;
	funcArr[i++] = &CallInterface::sbHeightcontrolClosed;
	funcArr[i++] = &CallInterface::sbGateOpen;
	funcArr[i++] = &CallInterface::sbGateClosed;
	funcArr[i++] = &CallInterface::msMetalTrue;
	funcArr[i++] = &CallInterface::sbSlideOpen;
	funcArr[i++] = &CallInterface::sbSlideClosed;
	funcArr[i++] = &CallInterface::sbEndOpen;
	funcArr[i++] = &CallInterface::sbEndClosed;
	funcArr[i++] = &CallInterface::btnStartPressed;
	funcArr[i++] = &CallInterface::btnStartReleased;
	funcArr[i++] = &CallInterface::btnStopPressed;
	funcArr[i++] = &CallInterface::btnStopReleased;
	funcArr[i++] = &CallInterface::btnResetPressed;
	funcArr[i++] = &CallInterface::btnResetReleased;
	funcArr[i++] = &CallInterface::btnEstopPressed;
	funcArr[i++] = &CallInterface::btnEstopReleased;

}

Dispatcher::~Dispatcher() {
	if (instance != NULL) {
		delete[] funcArr;
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

void Dispatcher::execute(void*) {
	int rc;
	struct _pulse pulse;

	while(!isStopped()){
		//TODO wenn man auf einem channel mit 2 threads lauscht und thread1 bekommt den pulse zuerst, erhält thread2 ihn trotzdem oder nur einer von beiden?
		//TODO beide automaten mit gleichen funktionen auf das callinterface?!
		//TODO sollen die knoepfe schon ins ms4 funzen?
		rc = MsgReceivePulse(chid, &pulse, sizeof(pulse), NULL);
		if (rc < 0) {
			printf("Dispatcher: Error in recv pulse\n");
			if (isStopped()) {
				break;
			}
		}

		if(pulse.code == PULSE_FROM_ISRHANDLER){
			//werte pulseval aus
			printf("--------------------------------------------\nDispatcher recvieved pulse: %d\n",pulse.value);

			int funcIdx = pulse.value.sival_int;

			if(funcIdx == SB_START_OPEN) {
				PuckHandler::getInstance()->activatePuck();
				printf("Dispatcher called activatePuck \n");
			}

			for(uint32_t i = 0 ; i < controllersForFunc[funcIdx].size(); i++){
				(controllersForFunc[funcIdx].at(i)->*funcArr[funcIdx])();
			}
			printf("Dispatcher called func%d \n",funcIdx);
		}
	}
}

void Dispatcher::registerContextForFunc(int funcIdx, CallInterface* callInterface) {
	controllersForFunc[funcIdx].push_back(callInterface);
}

void Dispatcher::registerContextForAllFuncs(CallInterface* callInterface) {
	for(int i = 0; i < MESSAGES_SIZE; i++){
		controllersForFunc[i].push_back(callInterface);
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
