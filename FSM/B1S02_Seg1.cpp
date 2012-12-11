/*
 * B1S02_Seg1.cpp
 *
 *  Created on: 24.11.2012
 *      Author: martin
 */

#include "B1S02_Seg1.h"

B1S02_Seg1::B1S02_Seg1(Controller* controller) {
	this->controller = controller;

	//TODO im extry aka exit im state b4 machen
	this->controller->setSegTimerMinCalled(false);
	this->controller->segTimerMin = timerHandler->createTimer(puckHandler->getDispChid(), TIME_VALUE_SEG1_MIN_SEC, TIME_VALUE_SEG1_MIN_MSEC, TIMER_SEG1_MIN);
	this->controller->segTimerMax = timerHandler->createTimer(puckHandler->getDispChid(), TIME_VALUE_SEG1_MAX_SEC, TIME_VALUE_SEG1_MAX_MSEC, TIMER_SEG1_MAX);
	this->controller->segTimerMin->start();
	this->controller->segTimerMax->start();

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
			//printf("Puck%d being p0pped\n", this->controller->getID());
		} else {
			//TODO: Throw MIN Error !!!
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
		// TODO: Throw MAX Error !!!
		int errorfsmChid = errfsm->getErrorFSMChid();
		int errorfsmCoid;
		int rc;

		if ((errorfsmCoid = ConnectAttach(0, 0, errorfsmChid, _NTO_SIDE_CHANNEL, 0)) == -1) {
			printf("B1S02_Seg1: Error in ConnectAttach\n");
		}

		rc = MsgSendPulse(errorfsmCoid, SIGEV_PULSE_PRIO_INHERIT, PULSE_FROM_PUCK, ERR_STATE_CRITICAL_ERROR);
		if (rc < 0) {
			printf("B1S02_Seg1: Error in MsgSendPulse");
		}

		if (ConnectDetach(errorfsmCoid) == -1) {
			printf("B1S02_Seg1: Error in ConnectDetach\n");
		}
	}
}
