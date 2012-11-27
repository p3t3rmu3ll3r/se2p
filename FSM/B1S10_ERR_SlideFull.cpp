/*
 * B1S10_ERR_SlideFull.cpp
 *
 *  Created on: 27.11.2012
 *      Author: aba079
 */

#include "B1S10_ERR_SlideFull.h"

B1S10_ERR_SlideFull::B1S10_ERR_SlideFull(Controller* controller) {
	this->controller = controller;

	//printf("DEBUG STATE: Puck%d -> B1S10_ERR_SlideFull \n", this->controller->getID());

	int replyChid = errfsm->getReplyChid();
	int errorfsmChid = errfsm->getErrorFSMChid();
	int errorfsmCoid;
	int rc;

	struct _pulse pulse;

	if ((errorfsmCoid = ConnectAttach(0, 0, errorfsmChid, _NTO_SIDE_CHANNEL, 0)) == -1) {
		printf("B1S10_ERR_SlideFull: Error in ConnectAttach\n");
	}

	rc = MsgSendPulse(errorfsmCoid, SIGEV_PULSE_PRIO_INHERIT, PULSE_FROM_PUCK, ERR_STATE_SLIDE_FULL);
	if (rc < 0) {
		printf("B1S10_ERR_SlideFull: Error in MsgSendPulse");
	}

	rc = MsgReceivePulse(replyChid, &pulse, sizeof(pulse), NULL);
	if (rc < 0) {
		printf("B1S10_ERR_SlideFull: Error in recv pulse\n");
	}

	this->controller->puckType = PUCK_ACCEPTED;

	if (ConnectDetach(errorfsmCoid) == -1) {
		printf("B1S10_ERR_SlideFull: Error in ConnectDetach\n");
	}

	new (this) B1S06_Slide(this->controller);
}

B1S10_ERR_SlideFull::~B1S10_ERR_SlideFull() {
}
