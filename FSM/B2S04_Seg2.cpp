/*
 * B2S04_Seg2.cpp
 *
 *  Created on: 25.11.2012
 *      Author: martin
 */

#include "B2S04_Seg2.h"

B2S04_Seg2::B2S04_Seg2(Controller* controller) {
	this->controller = controller;

#ifdef DEBUG_STATE_PRINTF
	printf("DEBUG STATE: Puck%d -> B2S04_Seg2\n", this->controller->getID());
#endif
}

B2S04_Seg2::~B2S04_Seg2() {
}

void B2S04_Seg2::sbGateOpen() {
	if(this->controller->isSegTimerMinCalled()){
		controller->resetSegTimers();

		new (this) B2S05_Gate(controller);
	} else {

		int errorfsmChid = errfsm->getErrorFSMChid();
		int errorfsmCoid;
		int rc;

		if ((errorfsmCoid = ConnectAttach(0, 0, errorfsmChid, _NTO_SIDE_CHANNEL, 0)) == -1) {
			printf("B2S04_Seg2: Error in ConnectAttach\n");
		}

		rc = MsgSendPulse(errorfsmCoid, SIGEV_PULSE_PRIO_INHERIT, PULSE_FROM_PUCK, ERR_STATE_ERROR);
		if (rc < 0) {
			printf("B2S04_Seg2: Error in MsgSendPulse");
		}

		if (ConnectDetach(errorfsmCoid) == -1) {
			printf("B2S04_Seg2: Error in ConnectDetach\n");
		}
	}
}

void B2S04_Seg2::msMetalTrue() {
	this->controller->puckType = PUCK_METAL;
}

void B2S04_Seg2::timerSeg2Min() {
	controller->setSegTimerMinCalled(true);
}

void B2S04_Seg2::timerSeg2Max() {
	int errorfsmChid = errfsm->getErrorFSMChid();
	int errorfsmCoid;
	int rc;

	if ((errorfsmCoid = ConnectAttach(0, 0, errorfsmChid, _NTO_SIDE_CHANNEL, 0)) == -1) {
		printf("B2S04_Seg2: Error in ConnectAttach\n");
	}

	//rc = MsgSendPulse(errorfsmCoid, SIGEV_PULSE_PRIO_INHERIT, PULSE_FROM_PUCK, ERR_STATE_CRITICAL_ERROR);
	rc = MsgSendPulse(errorfsmCoid, SIGEV_PULSE_PRIO_INHERIT, PULSE_FROM_PUCK, ERR_STATE_ERROR);
	if (rc < 0) {
		printf("B2S04_Seg2: Error in MsgSendPulse");
	}

	if (ConnectDetach(errorfsmCoid) == -1) {
		printf("B2S04_Seg2: Error in ConnectDetach\n");
	}

	puckHandler->removePuckFromBand(controller);
	if(puckHandler->isBandEmpty()){
		actorHAL->engineStop();
	}
	controller->resetController();
}
