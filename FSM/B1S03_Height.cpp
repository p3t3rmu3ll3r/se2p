/*
 * B1S03_Height.cpp
 *
 *  Created on: 24.11.2012
 *      Author: martin
 */

#include "B1S03_Height.h"

B1S03_Height::B1S03_Height(Controller* controller) {
	this->controller = controller;

	//printf("DEBUG STATE: Puck%d -> B1S03_Height \n", this->controller->getID());
	actorHAL->engineStop();
	controller->puckType = sensorHAL->getHeightPuckType();
	actorHAL->engineUnstop();
}

B1S03_Height::~B1S03_Height() {
}

void B1S03_Height::sbHeightcontrolClosed() {
	puckHandler->addPuckToSeg2(controller);
	new (this) B1S04_Seg2(controller);
}
