/*
 * B2S08_End.cpp
 *
 *  Created on: 25.11.2012
 *      Author: martin
 */

#include "B2S08_End.h"

B2S08_End::B2S08_End(Controller* controller) {
	this->controller = controller;

	printf("DEBUG STATE: Puck%d -> B2S08_End \n", this->controller->getID());
}

B2S08_End::~B2S08_End() {
}

void B2S08_End::sbEndClosed(){
	puckHandler->removePuckFromBand(controller);
	if(controller->isBand1Waiting()){
		rs232_1->sendMsg(RS232_BAND2_READY);
	}
	controller->resetController();
}
