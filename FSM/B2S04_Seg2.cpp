/*
 * B2S04_Seg2.cpp
 *
 *  Created on: 25.11.2012
 *      Author: martin
 */

#include "B2S04_Seg2.h"

B2S04_Seg2::B2S04_Seg2(Controller* controller) {
	this->controller = controller;
	puckHandler->addPuckToSeg2(controller);

	printf("DEBUG STATE: Puck%d -> B2S04_Seg2\n", this->controller->getID());
}

B2S04_Seg2::~B2S04_Seg2() {
}

void B2S04_Seg2::sbGateOpen() {
	puckHandler->removePuckFromSeg2();
	new (this) B2S05_Gate(controller);
}

void B2S04_Seg2::msMetalTrue() {
	this->controller->puckType = PUCK_METAL;
}
