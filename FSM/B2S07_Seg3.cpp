/*
 * B2S07_Seg3.cpp
 *
 *  Created on: 25.11.2012
 *      Author: martin
 */

#include "B2S07_Seg3.h"

B2S07_Seg3::B2S07_Seg3(Controller* controller) {
	this->controller = controller;

#ifdef DEBUG_STATE_PRINTF
	printf("DEBUG STATE: Puck%d -> B2S07_Seg3\n", this->controller->getID());
#endif
}

B2S07_Seg3::~B2S07_Seg3() {
}

void B2S07_Seg3::sbEndOpen() {
	if(this->controller->isSegTimerMinCalled()){
		controller->resetSegTimers();

		actorHAL->engineStop();
		new (this) B2S08_End(controller);
	} else {

		int errorfsmChid = errfsm->getErrorFSMChid();
		int errorfsmCoid;
		int rc;

		if ((errorfsmCoid = ConnectAttach(0, 0, errorfsmChid, _NTO_SIDE_CHANNEL, 0)) == -1) {
			printf("B2S07_Seg3: Error in ConnectAttach\n");
		}

		rc = MsgSendPulse(errorfsmCoid, SIGEV_PULSE_PRIO_INHERIT, PULSE_FROM_PUCK, ERR_STATE_ERROR);
		if (rc < 0) {
			printf("B2S07_Seg3: Error in MsgSendPulse");
		}

		if (ConnectDetach(errorfsmCoid) == -1) {
			printf("B2S07_Seg3: Error in ConnectDetach\n");
		}
	}
}

void B2S07_Seg3::timerGateClose() {
	actorHAL->gate(false);
	timerHandler->deleteTimer(this->controller->gateTimer);
}

void B2S07_Seg3::timerSeg3Min() {
	if(controller->isFirstElementInSegment()) {
		controller->setSegTimerMinCalled(true);
	}
}

void B2S07_Seg3::timerSeg3Max() {
	if(controller->isFirstElementInSegment()) {

		int errorfsmChid = errfsm->getErrorFSMChid();
		int errorfsmCoid;
		int rc;

		if ((errorfsmCoid = ConnectAttach(0, 0, errorfsmChid, _NTO_SIDE_CHANNEL, 0)) == -1) {
			printf("B2S07_Seg3: Error in ConnectAttach\n");
		}

		//rc = MsgSendPulse(errorfsmCoid, SIGEV_PULSE_PRIO_INHERIT, PULSE_FROM_PUCK, ERR_STATE_CRITICAL_ERROR);
		rc = MsgSendPulse(errorfsmCoid, SIGEV_PULSE_PRIO_INHERIT, PULSE_FROM_PUCK, ERR_STATE_ERROR);
		if (rc < 0) {
			printf("B2S07_Seg3: Error in MsgSendPulse");
		}

		if (ConnectDetach(errorfsmCoid) == -1) {
			printf("B2S07_Seg3: Error in ConnectDetach\n");
		}
	}

	puckHandler->removePuckFromBand(controller);
	if(puckHandler->isBandEmpty()){
		actorHAL->engineStop();
	}
	controller->resetController();
}
