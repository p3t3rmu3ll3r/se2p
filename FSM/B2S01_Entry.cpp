/*
 * B2S01_Entry.cpp
 *
 *  Created on: 24.11.2012
 *      Author: martin
 */

#include "B2S01_Entry.h"

B2S01_Entry::B2S01_Entry(Controller* controller) {
	this->controller = controller;
	puckHandler->addPuckToBand(this->controller);

	printf("DEBUG STATE: Puck%d -> B2S01_Entry \n", this->controller->getID());
}

B2S01_Entry::~B2S01_Entry() {
}

void B2S01_Entry::sbStartOpen() {
	/* TODO eigentlich not needed if baender gekoppelt */
	actorHAL->engineRight(false);
	actorHAL->engineUnstop();
}

void B2S01_Entry::sbStartClosed() {
	new (this) B2S02_Seg1(controller);
}

