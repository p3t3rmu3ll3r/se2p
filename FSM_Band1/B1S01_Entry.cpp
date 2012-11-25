/*
 * B1S01_Entry.cpp
 *
 *  Created on: 24.11.2012
 *      Author: martin
 */

#include "B1S01_Entry.h"

B1S01_Entry::B1S01_Entry(Controller* controller) {
	this->controller = controller;
	puckHandler->addPuckToBand1(this->controller);

	printf("DEBUG STATE: Puck%d -> B1S01_Entry \n", this->controller->getID());
}

B1S01_Entry::~B1S01_Entry() {
}

void B1S01_Entry::sbStartOpen() {
	if(puckHandler->isOnlyOneElemeOnBand1()){
		actorHAL->engineRight(false);
		actorHAL->engineUnstop();
	}
}

void B1S01_Entry::sbStartClosed() {
	new (this) B1S02_Seg1(controller);
}

