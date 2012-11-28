/*
 * B1S04_Seg2.cpp
 *
 *  Created on: 25.11.2012
 *      Author: martin
 */

#include "B1S04_Seg2.h"

B1S04_Seg2::B1S04_Seg2(Controller* controller) {
	this->controller = controller;

	//printf("DEBUG STATE: Puck%d -> B1S04_Seg2\n", this->controller->getID());

	this->controller->setFirstElementInSegment(puckHandler->checkIfFirstElemInSeg2(this->controller));
}

B1S04_Seg2::~B1S04_Seg2() {
}

void B1S04_Seg2::sbGateOpen() {
	if(controller->isFirstElementInSegment()) {
		puckHandler->removePuckFromSeg2();
		new (this) B1S05_Gate(controller);
	} else {
		new (this) B1S04_Seg2(controller);
	}
}
