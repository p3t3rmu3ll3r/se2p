/*
 * B1S04_Seg2.cpp
 *
 *  Created on: 25.11.2012
 *      Author: martin
 */

#include "B1S04_Seg2.h"

B1S04_Seg2::B1S04_Seg2(Controller* controller) {
	this->controller = controller;
	puckHandler->addPuckToSeg2(controller);

	printf("DEBUG STATE: Puck%d -> B1S04_Seg2\n", this->controller->getID());

	this->controller->setFirstElementInSegment(puckHandler->checkIfFirstElemInSeg2(this->controller));
	if(this->controller->puckType == PUCK_ACCEPTED || this->controller->puckType == PUCK_TURNOVER){
		actorHAL->gate(true);
	}
}

B1S04_Seg2::~B1S04_Seg2() {
}

void B1S04_Seg2::sbGateOpen() {
	if(controller->isFirstElementInSegment()) {
		new (this) B1S05_Gate(controller);
		puckHandler->removePuckFromSeg2();
	} else {
		new (this) B1S04_Seg2(controller);
	}
}
