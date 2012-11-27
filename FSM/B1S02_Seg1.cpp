/*
 * B1S02_Seg1.cpp
 *
 *  Created on: 24.11.2012
 *      Author: martin
 */

#include "B1S02_Seg1.h"

B1S02_Seg1::B1S02_Seg1(Controller* controller) {
	this->controller = controller;
	puckHandler->addPuckToSeg1(controller);

	//printf("DEBUG STATE: Puck%d -> B1S02_Seg1 \n", this->controller->getID());

	this->controller->setFirstElementInSegment(puckHandler->checkIfFirstElemInSeg1(this->controller));
}

B1S02_Seg1::~B1S02_Seg1() {

}

void B1S02_Seg1::sbHeightcontrolOpen() {
	if(controller->isFirstElementInSegment()) {
		puckHandler->removePuckFromSeg1();
		printf("Puck%d being p0pped\n", this->controller->getID());
		new (this) B1S03_Height(controller);
	} else {
		new (this) B1S02_Seg1(controller);
	}
}
