/*
 * B1S05_Gate.cpp
 *
 *  Created on: 25.11.2012
 *      Author: martin
 */

#include "B1S05_Gate.h"

B1S05_Gate::B1S05_Gate(Controller* controller) {
	this->controller = controller;

	//printf("DEBUG STATE: Puck%d -> B1S05_Gate \n", this->controller->getID());

	if(this->controller->puckType == PUCK_ACCEPTED || this->controller->puckType == PUCK_TURNOVER){
		actorHAL->gate(true);
	}
}

B1S05_Gate::~B1S05_Gate() {
}

void B1S05_Gate::sbGateClosed(){
	if(this->controller->puckType == PUCK_ACCEPTED || this->controller->puckType == PUCK_TURNOVER){
		new (this) B1S07_Seg3(controller);
	}
}

void B1S05_Gate::sbSlideOpen(){
	new (this) B1S06_Slide(controller);
}

