/*
 * State2.cpp
 *
 *  Created on: 24.11.2012
 *      Author: martin
 */

#include "State2.h"

State2::State2(Controller* controller) {
	printf("DEBUG STATE: State2 \n");
	this->controller = controller;
	puckHandler->addPuckToSeg1(controller);

	printf("starting initializing isFirstElementInSegment... \n");
	this->controller->setFirstElementInSegment(puckHandler->checkIfFirstElemInSeg1(this->controller));
	printf("finished initializing isFirstElementInSegment... \n");
}

State2::~State2() {

}

void State2::sbHeightcontrolOpen() {
	if(controller->isFirstElementInSegment()) {
		new (this) State3(controller);
	} else {
		new (this) State2(controller);
	}
}
