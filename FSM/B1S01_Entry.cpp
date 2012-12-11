/*
 * B1S01_Entry.cpp
 *
 *  Created on: 24.11.2012
 *      Author: martin
 */

#include "B1S01_Entry.h"

B1S01_Entry::B1S01_Entry(Controller* controller) {
	this->controller = controller;
	puckHandler->addPuckToBand(this->controller);

	//printf("DEBUG STATE: Puck%d -> B1S01_Entry \n", this->controller->getID());
}

B1S01_Entry::~B1S01_Entry() {
}

void B1S01_Entry::sbStartOpen() {
	if(puckHandler->isOnlyOneElemeOnBand()){
		actorHAL->engineRight(false);
		actorHAL->engineUnstop();
	}
}

void B1S01_Entry::sbStartClosed() {
	puckHandler->addPuckToSeg1(controller);

	this->controller->setSegTimerMinCalled(false);
	this->controller->segTimerMin = timerHandler->createTimer(puckHandler->getDispChid(), TIME_VALUE_SEG1_MIN_SEC, TIME_VALUE_SEG1_MIN_MSEC, TIMER_SEG1_MIN);
	this->controller->segTimerMax = timerHandler->createTimer(puckHandler->getDispChid(), TIME_VALUE_SEG1_MAX_SEC, TIME_VALUE_SEG1_MAX_MSEC, TIMER_SEG1_MAX);
	this->controller->segTimerMin->start();
	this->controller->segTimerMax->start();

	new (this) B1S02_Seg1(controller);
}

