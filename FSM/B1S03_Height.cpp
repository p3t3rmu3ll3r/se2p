/*
 * B1S03_Height.cpp
 *
 *  Created on: 24.11.2012
 *      Author: martin
 */

#include "B1S03_Height.h"

B1S03_Height::B1S03_Height(Controller* controller) {
	this->controller = controller;

#ifdef DEBUG_STATE_PRINTF
	printf("DEBUG STATE: Puck%d -> B1S03_Height \n", this->controller->getID());
#endif
	timerHandler->pauseAllTimers();
	actorHAL->engineStop();
	controller->puckType = sensorHAL->getHeightPuckType();
	actorHAL->engineUnstop();
	timerHandler->continueAllTimers();
}

B1S03_Height::~B1S03_Height() {
}

void B1S03_Height::sbHeightcontrolClosed() {
	puckHandler->addPuckToSeg2(controller);

	this->controller->setSegTimerMinCalled(false);
	this->controller->segTimerMin = timerHandler->createTimer(puckHandler->getDispChid(), TIME_VALUE_SEG2_MIN_SEC, TIME_VALUE_SEG2_MIN_MSEC, TIMER_SEG2_MIN);
	this->controller->segTimerMax = timerHandler->createTimer(puckHandler->getDispChid(), TIME_VALUE_SEG2_MAX_SEC, TIME_VALUE_SEG2_MAX_MSEC, TIMER_SEG2_MAX);
	this->controller->segTimerMin->start();
	this->controller->segTimerMax->start();

	new (this) B1S04_Seg2(controller);
}
