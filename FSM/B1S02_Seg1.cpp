/*
 * B1S02_Seg1.cpp
 *
 *  Created on: 24.11.2012
 *      Author: martin
 */

#include "B1S02_Seg1.h"

B1S02_Seg1::B1S02_Seg1(Controller* controller) {
	this->controller = controller;

	this->controller->setSegTimerMinCalled(false);
	this->controller->segTimerMin = timerHandler->createTimer(puckHandler->getDispChid(), 0, TIME_VALUE_SEG1_MIN, TIMER_SEG1_MIN);
	this->controller->segTimerMax = timerHandler->createTimer(puckHandler->getDispChid(), 0, TIME_VALUE_SEG1_MAX, TIMER_SEG1_MAX);

	//printf("DEBUG STATE: Puck%d -> B1S02_Seg1 \n", this->controller->getID());

	this->controller->setFirstElementInSegment(puckHandler->checkIfFirstElemInSeg1(this->controller));
}

B1S02_Seg1::~B1S02_Seg1() {

}

void B1S02_Seg1::sbHeightcontrolOpen() {
	if(controller->isFirstElementInSegment()) {
		if(this->controller->isSegTimerMinCalled()){
			controller->resetSegTimers();

			puckHandler->removePuckFromSeg1();
			new (this) B1S03_Height(controller);
			//printf("Puck%d being p0pped\n", this->controller->getID());
		} else {
			//TODO: Throw MIN Error !!!
		}
	} else {
		new (this) B1S02_Seg1(controller);
	}
}

void B1S02_Seg1::timerSeg1Min() {
	if(controller->isFirstElementInSegment()) {
		controller->setSegTimerMinCalled(true);
	}
}

void B1S02_Seg1::timerSeg1Max() {
	if(controller->isFirstElementInSegment()) {
		// TODO: Throw MAX Error !!!
	}
}
