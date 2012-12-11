/*
 * B1S02_Seg1.cpp
 *
 *  Created on: 24.11.2012
 *      Author: martin
 */

#include "B1S02_Seg1.h"

B1S02_Seg1::B1S02_Seg1(Controller* controller) {
	this->controller = controller;

	//printf("DEBUG STATE: Puck%d -> B1S02_Seg1 \n", this->controller->getID());

	this->controller->setFirstElementInSegment(puckHandler->checkIfFirstElemInSeg1(this->controller));
}

B1S02_Seg1::~B1S02_Seg1() {

}

void B1S02_Seg1::sbHeightcontrolOpen() {
	if(controller->isFirstElementInSegment()) {
		if(this->controller->isSegTimerMinCalled()){
			controller->resetSegTimers();

			puckHandler->removePuckFromSeg1();
			new (this) B1S03_Height(controller);
		} else {

			int errorfsmChid = errfsm->getErrorFSMChid();
			int errorfsmCoid;
			int rc;

			if ((errorfsmCoid = ConnectAttach(0, 0, errorfsmChid, _NTO_SIDE_CHANNEL, 0)) == -1) {
				printf("B1S02_Seg1: Error in ConnectAttach\n");
			}

			rc = MsgSendPulse(errorfsmCoid, SIGEV_PULSE_PRIO_INHERIT, PULSE_FROM_PUCK, ERR_STATE_ERROR);
			if (rc < 0) {
				printf("B1S02_Seg1: Error in MsgSendPulse");
			}

			if (ConnectDetach(errorfsmCoid) == -1) {
				printf("B1S02_Seg1: Error in ConnectDetach\n");
			}
		}
	} else {
		new (this) B1S02_Seg1(controller);
	}
}

void B1S02_Seg1::timerSeg1Min() {
	if(controller->isFirstElementInSegment()) {
		controller->setSegTimerMinCalled(true);
	}
}

void B1S02_Seg1::timerSeg1Max() {
	printf("B1S02_Seg1: timerSeg1Max\n");
	if(controller->isFirstElementInSegment()) {
		printf("B1S02_Seg1: timerSeg1Max -> isFirstElementInSegment\n");

		int errorfsmChid = errfsm->getErrorFSMChid();
		int errorfsmCoid;
		int rc;

		if ((errorfsmCoid = ConnectAttach(0, 0, errorfsmChid, _NTO_SIDE_CHANNEL, 0)) == -1) {
			printf("B1S02_Seg1: Error in ConnectAttach\n");
		}

		//rc = MsgSendPulse(errorfsmCoid, SIGEV_PULSE_PRIO_INHERIT, PULSE_FROM_PUCK, ERR_STATE_CRITICAL_ERROR);
		rc = MsgSendPulse(errorfsmCoid, SIGEV_PULSE_PRIO_INHERIT, PULSE_FROM_PUCK, ERR_STATE_ERROR);
		if (rc < 0) {
			printf("B1S02_Seg1: Error in MsgSendPulse");
		}

		if (ConnectDetach(errorfsmCoid) == -1) {
			printf("B1S02_Seg1: Error in ConnectDetach\n");
		}
	}

	puckHandler->removePuckFromBand(controller);
	if(puckHandler->isBandEmpty()){
		actorHAL->engineStop();
	}
	controller->resetController();
}
