/*
 * B2S10_ERR_SlideFull.cpp
 *
 *  Created on: 27.11.2012
 *      Author: aba079
 */

#include "B2S10_ERR_SlideFull.h"

B2S10_ERR_SlideFull::B2S10_ERR_SlideFull(Controller* controller) {
	this->controller = controller;

#ifdef DEBUG_STATE_PRINTF
	printf("DEBUG STATE: Puck%d -> B2S10_ERR_SlideFull \n", this->controller->getID());
#endif

	int replyChid = errfsm->getReplyChid();
	int errorfsmChid = errfsm->getErrorFSMChid();
	int errorfsmCoid;
	int rc;

	struct _pulse pulse;

	if ((errorfsmCoid = ConnectAttach(0, 0, errorfsmChid, _NTO_SIDE_CHANNEL, 0)) == -1) {
		printf("B2S10_ERR_SlideFull: Error in ConnectAttach\n");
	}

	rc = MsgSendPulse(errorfsmCoid, SIGEV_PULSE_PRIO_INHERIT, PULSE_FROM_PUCK, ERR_STATE_SLIDE_FULL);
	if (rc < 0) {
		printf("B2S10_ERR_SlideFull: Error in MsgSendPulse");
	}

	rc = MsgReceivePulse(replyChid, &pulse, sizeof(pulse), NULL);
	if (rc < 0) {
		printf("B2S10_ERR_SlideFull: Error in recv pulse\n");
	}

	if (ConnectDetach(errorfsmCoid) == -1) {
		printf("B2S10_ERR_SlideFull: Error in ConnectDetach\n");
	}

	//new (this) B2S06_Slide(this->controller); //TODO: not necessary

	//TODO: Diagramme anpassen

	//new (this) B2S06_Slide(this->controller);
	puckHandler->removePuckFromBand(controller);
	actorHAL->engineStop();
	if(controller->isBand1Waiting()){
		rs232_1->sendMsg(RS232_BAND2_READY);
		ActorHAL::getInstance()->engineRight(false);
		ActorHAL::getInstance()->engineUnstop();
	}
	controller->resetController();
}

B2S10_ERR_SlideFull::~B2S10_ERR_SlideFull() {
}
