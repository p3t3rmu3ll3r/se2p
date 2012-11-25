/*
 * B1S07_Seg3.cpp
 *
 *  Created on: 25.11.2012
 *      Author: martin
 */

#include "B1S07_Seg3.h"

B1S07_Seg3::B1S07_Seg3(Controller* controller) {
	this->controller = controller;
	puckHandler->addPuckToSeg3(controller);

	printf("DEBUG STATE: Puck%d -> B1S07_Seg3\n", this->controller->getID());

	//TODO 2 chk if ok
	actorHAL->gate(false);

	this->controller->setFirstElementInSegment(
			puckHandler->checkIfFirstElemInSeg3(this->controller));
}

B1S07_Seg3::~B1S07_Seg3() {
}

void B1S07_Seg3::sbEndOpen() {
	if (controller->isFirstElementInSegment()) {
		new (this) B1S08_End(controller);
		puckHandler->removePuckFromSeg3();
 	} else {
		new (this) B1S07_Seg3(controller);
	}
}
