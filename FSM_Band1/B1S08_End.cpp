/*
 * B1S08_End.cpp
 *
 *  Created on: 25.11.2012
 *      Author: martin
 */

#include "B1S08_End.h"

B1S08_End::B1S08_End(Controller* controller) {
	this->controller = controller;

	printf("DEBUG STATE: Puck%d -> B1S08_End \n", this->controller->getID());
}

B1S08_End::~B1S08_End() {
}

void B1S08_End::sbEndClosed(){
	puckHandler->removePuckFromBand1(controller);
	if(puckHandler->isBand1Empty()){
		actorHAL->engineStop();
	}
	controller->resetController();
}
