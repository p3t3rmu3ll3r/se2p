/*
 * B2S06_Slide.cpp
 *
 *  Created on: 25.11.2012
 *      Author: martin
 */

#include "B2S06_Slide.h"

B2S06_Slide::B2S06_Slide(Controller* controller) {
	this->controller = controller;

	this->controller->slideTimer = timerHandler->createTimer(puckHandler->getDispChid(), TIME_VALUE_SLIDE_FULL_SEC, TIME_VALUE_SLIDE_FULL_MSEC, TIMER_SLIDE_FULL);
	this->controller->slideTimer->start();

#ifdef DEBUG_STATE_PRINTF
	printf("DEBUG STATE: Puck%d -> B2S06_Slide \n", this->controller->getID());
#endif
}

B2S06_Slide::~B2S06_Slide() {
}

void B2S06_Slide::sbSlideClosed(){
	puckHandler->removePuckFromBand(controller);
	actorHAL->engineStop();
	if(controller->isBand1Waiting()){
		rs232_1->sendMsg(RS232_BAND2_READY);
		ActorHAL::getInstance()->engineRight(false);
		ActorHAL::getInstance()->engineUnstop();
	}
	controller->resetController();
}

void B2S06_Slide::timerSlideFull(){
	new (this) B2S10_ERR_SlideFull(controller);
}
