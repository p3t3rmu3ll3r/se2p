/**
 * SE2 WiSe 2012
 * Festo Dispatcher
 *
 * Dispatcher forwards Pulse Messages received from the ISRHandler and RS232 to
 * all registered Controllers. Each Controller represents a puck on the band conveyor.
 * Controllers need the messages to do their transitions to get into another state.
 * The Dispatcher is part of the controller/reactor mechanism for the state pattern
 *
 * @file Dispatcher.cpp
 * @author Chris Addo
 *         Jens Eberwein
 *         Tristan Rudat
 *         Martin Slowikowski
 * @date 2012-11-28
 * @version 0.4
 *
 */

#include "PuckHandler.h"

Dispatcher* Dispatcher::instance = NULL;
Mutex* Dispatcher::dispatcherInstanceMutex = new Mutex();

Dispatcher::Dispatcher() {
	//Create channel for pulse notification
	if ((chid = ChannelCreate(0)) == -1) {
		printf("Dispatcher: Error in ChannelCreate\n");
	}

	// Initialize *fp Array, set up all possible signals
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

	lc = LightController::getInstance();
	eStop = false;
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
	bool isRunning = false;

	struct _pulse pulse;

	while(!isStopped()){
		rc = MsgReceivePulse(chid, &pulse, sizeof(pulse), NULL);
		if (rc < 0) {
			printf("Dispatcher: Error in recv pulse\n");
			if (isStopped()) {
				break;
			}
		}

		if (pulse.code == PULSE_FROM_ISRHANDLER) {
			int funcIdx = pulse.value.sival_int;

			if(funcIdx == BTN_START_PRESSED && !isRunning && !eStop){
				isRunning = true;
				lc->operatingNormal();
			} else if(funcIdx == BTN_STOP_PRESSED && isRunning && !eStop){
				isRunning = false;
			}

			if(isRunning && !eStop){
#ifdef DEBUG_DISPATCHER
				printf("--------------------------------------------\n");
				printf("Dispatcher received ISR pulse: %d\n", pulse.value);
#endif

				if (funcIdx == SB_START_OPEN) {
					PuckHandler::getInstance()->activatePuck();
#ifdef DEBUG_DISPATCHER
					printf("Dispatcher called activatePuck \n");
#endif
				}

				for (uint32_t i = 0; i < controllersForFunc[funcIdx].size(); i++) {
					(controllersForFunc[funcIdx].at(i)->*funcArr[funcIdx])();
				}
#ifdef DEBUG_DISPATCHER
				printf("Dispatcher called func%d \n", funcIdx);
#endif
			}
		} else if(pulse.code == PULSE_FROM_RS232){
			//int codeSer = pulse.value.sival_int;
			//printf("Dispatcher received RS232 pulse: %d\n", codeSer);
		} else if(pulse.code == PULSE_FROM_ERR_FSM) {
			// wenn PULSE_FROM_ISRHANDLER ein estop bemerkt, running auf false setzen, kein dispatchen mehr
			// setze hier running bool zurueck auf true
		}
	}
}

void Dispatcher::registerContextForFunc(int funcIdx, CallInterface* callInterface) {
	controllersForFunc[funcIdx].push_back(callInterface);
}

void Dispatcher::registerContextForAllFuncs(CallInterface* callInterface) {
	for (int i = 0; i < MESSAGES_SIZE; i++) {
		controllersForFunc[i].push_back(callInterface);
	}
}

void Dispatcher::stop() {
	HAWThread::stop();

	if (ChannelDestroy(chid) == -1) {
		printf("Dispatcher: Error in ChannelDestroy\n");
	}
}

void Dispatcher::shutdown() {
}

int Dispatcher::getChid() {
	return chid;
}

void Dispatcher::setEstop(bool eStop) {
	this->eStop = eStop;
}
