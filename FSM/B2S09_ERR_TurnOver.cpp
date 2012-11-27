/*
 * B2S09_ERR_TurnOver.cpp
 *
 *  Created on: 27.11.2012
 *      Author: aba079
 */

#include "B2S09_ERR_TurnOver.h"

B2S09_ERR_TurnOver::B2S09_ERR_TurnOver(Controller* controller) {
	this->controller = controller;

	printf("DEBUG STATE: Puck%d -> B2S09_ERR_TurnOver \n", this->controller->getID());

	int replyChid = errfsm->getReplyChid();
	int errorfsmChid = errfsm->getErrorFSMChid();
	int errorfsmCoid;
	int rc;

	struct _pulse pulse;

	if ((errorfsmCoid = ConnectAttach(0, 0, errorfsmChid, _NTO_SIDE_CHANNEL, 0)) == -1) {
		printf("B2S09_ERR_TurnOver: Error in ConnectAttach\n");
	}

	rc = MsgSendPulse(errorfsmCoid, SIGEV_PULSE_PRIO_INHERIT, PULSE_FROM_PUCK, ERR_STATE_TURNOVER_BAND2);
	if (rc < 0) {
		printf("B2S09_ERR_TurnOver: Error in MsgSendPulse");
	}

	rc = MsgReceivePulse(replyChid, &pulse, sizeof(pulse), NULL);
	if (rc < 0) {
		printf("B2S09_ERR_TurnOver: Error in recv pulse\n");
	}

	this->controller->puckType = -1;

	if (ConnectDetach(errorfsmCoid) == -1) {
		printf("B2S09_ERR_TurnOver: Error in ConnectDetach\n");
	}

}

B2S09_ERR_TurnOver::~B2S09_ERR_TurnOver() {
}

void B2S09_ERR_TurnOver::sbStartClosed(){
	new (this) B2S02_Seg1(this->controller);
}
