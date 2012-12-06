/*
 * B1S06_Slide.cpp
 *
 *  Created on: 25.11.2012
 *      Author: martin
 */

#include "B1S06_Slide.h"

B1S06_Slide::B1S06_Slide(Controller* controller) {
	this->controller = controller;

	this->controller->slideTimer = timerHandler->createTimer(puckHandler->getDispChid(), 0, TIME_VALUE_SLIDE_FULL, TIMER_SLIDE_FULL);
	this->controller->slideTimer->start();

	//printf("DEBUG STATE: Puck%d -> B1S06_Slide \n", this->controller->getID());

	//do timer magic for slidefull error
}

B1S06_Slide::~B1S06_Slide() {
}

void B1S06_Slide::sbSlideClosed(){
	puckHandler->removePuckFromBand(controller);
	if(puckHandler->isBandEmpty()){
		actorHAL->engineStop();
	}
	controller->resetController();
}

void B1S06_Slide::timerSlideFull(){
	new (this) B1S10_ERR_SlideFull(controller);
}

