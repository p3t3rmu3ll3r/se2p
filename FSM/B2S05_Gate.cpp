/*
 * B2S05_Gate.cpp
 *
 *  Created on: 25.11.2012
 *      Author: martin
 */

#include "B2S05_Gate.h"

B2S05_Gate::B2S05_Gate(Controller* controller) {
	this->controller = controller;

	printf("DEBUG STATE: Puck%d -> B2S05_Gate \n", this->controller->getID());

	if(this->controller->puckType == PUCK_ACCEPTED){
		actorHAL->gate(true);

		this->controller->gateTimer = timerHandler->createTimer(puckHandler->getDispChid(), TIME_VALUE_CLOSE_GATE_SEC, TIME_VALUE_CLOSE_GATE_MSEC, TIMER_GATE_CLOSE);
		this->controller->gateTimer->start();
	}
}

B2S05_Gate::~B2S05_Gate() {
}

void B2S05_Gate::sbGateClosed(){
	if(this->controller->puckType == PUCK_ACCEPTED){
		new (this) B2S07_Seg3(controller);
	}
}

void B2S05_Gate::sbSlideOpen(){
	new (this) B2S06_Slide(controller);
}

