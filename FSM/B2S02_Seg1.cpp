/*
 * B2S02_Seg1.cpp
 *
 *  Created on: 24.11.2012
 *      Author: martin
 */

#include "B2S02_Seg1.h"

B2S02_Seg1::B2S02_Seg1(Controller* controller) {
	this->controller = controller;

#ifdef DEBUG_STATE_PRINTF
	printf("DEBUG STATE: Puck%d -> B2S02_Seg1 \n", this->controller->getID());
#endif
}

B2S02_Seg1::~B2S02_Seg1() {
	rs232_1->sendMsg(RS232_PUCK_ARRIVED_ON_BAND2);
}

void B2S02_Seg1::sbHeightcontrolOpen() {
	if(this->controller->isSegTimerMinCalled()){
		controller->resetSegTimers();

		new (this) B2S03_Height(controller);
	} else {

		int errorfsmChid = errfsm->getErrorFSMChid();
		int errorfsmCoid;
		int rc;

		if ((errorfsmCoid = ConnectAttach(0, 0, errorfsmChid, _NTO_SIDE_CHANNEL, 0)) == -1) {
			printf("B2S02_Seg1: Error in ConnectAttach\n");
		}

		rc = MsgSendPulse(errorfsmCoid, SIGEV_PULSE_PRIO_INHERIT, PULSE_FROM_PUCK, ERR_STATE_ERROR);
		if (rc < 0) {
			printf("B2S02_Seg1: Error in MsgSendPulse");
		}

		if (ConnectDetach(errorfsmCoid) == -1) {
			printf("B2S02_Seg1: Error in ConnectDetach\n");
		}
	}
}

void B2S02_Seg1::timerSeg1Min() {
	controller->setSegTimerMinCalled(true);
}

void B2S02_Seg1::timerSeg1Max() {
	int errorfsmChid = errfsm->getErrorFSMChid();
	int errorfsmCoid;
	int rc;

	if ((errorfsmCoid = ConnectAttach(0, 0, errorfsmChid, _NTO_SIDE_CHANNEL, 0)) == -1) {
		printf("B2S02_Seg1: Error in ConnectAttach\n");
	}

	//rc = MsgSendPulse(errorfsmCoid, SIGEV_PULSE_PRIO_INHERIT, PULSE_FROM_PUCK, ERR_STATE_CRITICAL_ERROR);
	rc = MsgSendPulse(errorfsmCoid, SIGEV_PULSE_PRIO_INHERIT, PULSE_FROM_PUCK, ERR_STATE_ERROR);
	if (rc < 0) {
		printf("B2S02_Seg1: Error in MsgSendPulse");
	}

	if (ConnectDetach(errorfsmCoid) == -1) {
		printf("B2S02_Seg1: Error in ConnectDetach\n");
	}

	puckHandler->removePuckFromBand(controller);
	if(puckHandler->isBandEmpty()){
		actorHAL->engineStop();
	}
	controller->resetController();
}
