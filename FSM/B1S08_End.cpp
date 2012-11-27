/*
 * B1S08_End.cpp
 *
 *  Created on: 25.11.2012
 *      Author: martin
 */

#include "B1S08_End.h"

B1S08_End::B1S08_End(Controller* controller) {
	this->controller = controller;

	//printf("DEBUG STATE: Puck%d -> B1S08_End \n", this->controller->getID());

	if(this->controller->puckType == PUCK_TURNOVER){
		new (this) B1S09_ERR_TurnOver(this->controller);
	}
}

B1S08_End::~B1S08_End() {
}

void B1S08_End::sbEndClosed(){
	puckHandler->removePuckFromBand(controller);
	if(puckHandler->isBand1Empty()){
		actorHAL->engineStop();
	}
	controller->resetController();
}
