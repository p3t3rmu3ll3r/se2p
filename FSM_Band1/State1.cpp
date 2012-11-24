/*
 * State1.cpp
 *
 *  Created on: 24.11.2012
 *      Author: martin
 */

#include "State1.h"

State1::State1(Controller* controller) {
	printf("DEBUG STATE: State1 \n");
	this->controller = controller;
}

State1::~State1() {
}

void State1::sbStartOpen() {
	if(puckHandler->isBand1Empty()){
		actorHAL->engineRight(false);
		actorHAL->engineUnstop();
	}
}

void State1::sbStartClosed() {
	new (this) State2(controller);
}

