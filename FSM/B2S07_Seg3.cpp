/*
 * B2S07_Seg3.cpp
 *
 *  Created on: 25.11.2012
 *      Author: martin
 */

#include "B2S07_Seg3.h"

B2S07_Seg3::B2S07_Seg3(Controller* controller) {
	this->controller = controller;

	printf("DEBUG STATE: Puck%d -> B2S07_Seg3\n", this->controller->getID());
}

B2S07_Seg3::~B2S07_Seg3() {
}

void B2S07_Seg3::sbEndOpen() {
	actorHAL->engineStop();
	new (this) B2S08_End(controller);
}
