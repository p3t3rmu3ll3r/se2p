/*
 * B2S07_Seg3.cpp
 *
 *  Created on: 25.11.2012
 *      Author: martin
 */

#include "B2S07_Seg3.h"

B2S07_Seg3::B2S07_Seg3(Controller* controller) {
	this->controller = controller;
	puckHandler->addPuckToSeg3(controller);

	printf("DEBUG STATE: Puck%d -> B2S07_Seg3\n", this->controller->getID());

	//TODO 2 chk if ok
	usleep(400000);
	actorHAL->gate(false);
}

B2S07_Seg3::~B2S07_Seg3() {
}

void B2S07_Seg3::sbEndOpen() {
	actorHAL->engineStop();
	puckHandler->removePuckFromSeg3();
	new (this) B2S08_End(controller);
}
