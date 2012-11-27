/*
 * B1S06_Slide.cpp
 *
 *  Created on: 25.11.2012
 *      Author: martin
 */

#include "B1S06_Slide.h"

B1S06_Slide::B1S06_Slide(Controller* controller) {
	this->controller = controller;

	//printf("DEBUG STATE: Puck%d -> B1S06_Slide \n", this->controller->getID());

	//do timer magic for slidefull error
}

B1S06_Slide::~B1S06_Slide() {
}

void B1S06_Slide::sbSlideClosed(){
	puckHandler->removePuckFromBand(controller);
	if(puckHandler->isBand1Empty()){
		actorHAL->engineStop();
	}
	controller->resetController();
}

