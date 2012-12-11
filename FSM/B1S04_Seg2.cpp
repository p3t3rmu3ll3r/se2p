/*
 * B1S04_Seg2.cpp
 *
 *  Created on: 25.11.2012
 *      Author: martin
 */

#include "B1S04_Seg2.h"

B1S04_Seg2::B1S04_Seg2(Controller* controller) {
	this->controller = controller;

	//printf("DEBUG STATE: Puck%d -> B1S04_Seg2\n", this->controller->getID());

	this->controller->setFirstElementInSegment(puckHandler->checkIfFirstElemInSeg2(this->controller));
}

B1S04_Seg2::~B1S04_Seg2() {
}

void B1S04_Seg2::sbGateOpen() {
	if(controller->isFirstElementInSegment()) {
		if(this->controller->isSegTimerMinCalled()){
			controller->resetSegTimers();

			puckHandler->removePuckFromSeg2();
			new (this) B1S05_Gate(controller);
		} else {

			int errorfsmChid = errfsm->getErrorFSMChid();
			int errorfsmCoid;
			int rc;

			if ((errorfsmCoid = ConnectAttach(0, 0, errorfsmChid, _NTO_SIDE_CHANNEL, 0)) == -1) {
				printf("B1S04_Seg2: Error in ConnectAttach\n");
			}

			rc = MsgSendPulse(errorfsmCoid, SIGEV_PULSE_PRIO_INHERIT, PULSE_FROM_PUCK, ERR_STATE_ERROR);
			if (rc < 0) {
				printf("B1S04_Seg2: Error in MsgSendPulse");
			}

			if (ConnectDetach(errorfsmCoid) == -1) {
				printf("B1S04_Seg2: Error in ConnectDetach\n");
			}
		}
	} else {
		new (this) B1S04_Seg2(controller);
	}
}

void B1S04_Seg2::timerSeg2Min() {
	if(controller->isFirstElementInSegment()) {
		controller->setSegTimerMinCalled(true);
	}
}

void B1S04_Seg2::timerSeg2Max() {
	printf("B1S04_Seg2: timerSeg2Max\n");
	if(controller->isFirstElementInSegment()) {
		printf("B1S04_Seg2: timerSeg2Max -> isFirstElementInSegment\n");

		int errorfsmChid = errfsm->getErrorFSMChid();
		int errorfsmCoid;
		int rc;

		if ((errorfsmCoid = ConnectAttach(0, 0, errorfsmChid, _NTO_SIDE_CHANNEL, 0)) == -1) {
			printf("B1S04_Seg2: Error in ConnectAttach\n");
		}

		rc = MsgSendPulse(errorfsmCoid, SIGEV_PULSE_PRIO_INHERIT, PULSE_FROM_PUCK, ERR_STATE_CRITICAL_ERROR);
		if (rc < 0) {
			printf("B1S04_Seg2: Error in MsgSendPulse");
		}

		if (ConnectDetach(errorfsmCoid) == -1) {
			printf("B1S04_Seg2: Error in ConnectDetach\n");
		}
	}
}
