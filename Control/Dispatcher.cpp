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
	//TODO eigentlich unnötig, genauso wie detach, da wir nur receiven, aber nicht senden
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
		rc = MsgReceivePulse(chid, &pulse, sizeof(pulse), NULL);
		if (rc < 0) {
			printf("Dispatcher: Error in recv pulse\n");
			if (isStopped()) {
				break;
			}
		}

		if (pulse.code == PULSE_FROM_ISRHANDLER) {
			//werte pulseval aus
			//printf("--------------------------------------------\n"
			//	   "Dispatcher received ISR pulse: %d\n",	pulse.value);

			int funcIdx = pulse.value.sival_int;
			//TODO ggf siwtch um alles bauen, um tasten abzufragen -> EStop und Ein/Aus, prog starten und beenden
			// solange EIN nicht pressed, nix dispatchen und nix tun ... if pressed, bool setzen ... gleiches bei stop,
			// natuerlich alles resetten ;)
			// if(funcIdx == ESTOP_BTNPRESSED) nix an die pucks weiterleiten und puckhandler estop(true) callen
			// if (funcIdx == ESTOP_BTNRELEASED) setze bool step1 auf true
			// if(funcIdx == RESET_BTNPRESSED) setze bool step2 auf true und alles rennt weiter, call puckhandler estop(false)
			// oder den button in die error fsm verlegen, wenn estop pushed wird, dispatcht dispatcher nix mehr, bis error
			// fsm sagt -> alles cool
			if (funcIdx == SB_START_OPEN) {
				PuckHandler::getInstance()->activatePuck();
				printf("Dispatcher called activatePuck \n");
			}

			for (uint32_t i = 0; i < controllersForFunc[funcIdx].size(); i++) {
				(controllersForFunc[funcIdx].at(i)->*funcArr[funcIdx])();
			}
			//printf("Dispatcher called func%d \n", funcIdx);
		} else if(pulse.code == PULSE_FROM_RS232){
			//TODO eigentlich unguenstig, dass hier xtra zu behandeln, eigentlich dispatcht
			//er ja auch nur n funktionsaufruf, is hier mom nur fuer debug, koennte doch oben mit rein oder?
			//also if (pulse.code == PULSE_FROM_ISRHANDLER || pulse.code == PULSE_FROM_RS232)
			int codeSer = pulse.value.sival_int;
			printf("Dispatcher received RS232 pulse: %d\n", codeSer);
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
