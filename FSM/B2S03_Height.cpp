/*
 * B2S03_Height.cpp
 *
 *  Created on: 24.11.2012
 *      Author: martin
 */

#include "B2S03_Height.h"

B2S03_Height::B2S03_Height(Controller* controller) {
	this->controller = controller;

	printf("DEBUG STATE: Puck%d -> B2S03_Height \n", this->controller->getID());

	actorHAL->engineStop();
	controller->puckType = sensorHAL->getHeightPuckType();
	actorHAL->engineUnstop();


	if(controller->puckType == PUCK_TURNOVER){
		new (this) B2S09_ERR_TurnOver(this->controller);
	}
}

B2S03_Height::~B2S03_Height() {
}

void B2S03_Height::sbHeightcontrolClosed() {
	new (this) B2S04_Seg2(controller);
}
