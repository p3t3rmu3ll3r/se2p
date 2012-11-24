/*
 * Controller.cpp
 *
 *  Created on: 21.11.2012
 *      Author: aay973
 */

#include "Controller.h"
#include "State1.h"

Controller::Controller() {
	firstElementInSegment = false;
}

Controller::~Controller() {

}

void Controller::sbStartOpen(){
	state = new State1(this);
	state->sbStartOpen();
}

void Controller::sbStartClosed(){state->sbStartClosed();}
void Controller::sbHeightcontrolOpen(){state->sbHeightcontrolOpen();}
void Controller::sbHeightcontrolClosed(){state->sbHeightcontrolOpen();}
void Controller::sbGateOpen(){state->sbGateOpen();}
void Controller::sbGateClosed(){state->sbGateClosed();}
void Controller::msMetalTrue(){state->sbGateClosed();}
void Controller::sbSlideOpen(){state->sbSlideOpen();}
void Controller::sbSlideClosed(){state->sbSlideClosed();}
void Controller::sbEndOpen(){state->sbEndOpen();}
void Controller::sbEndClosed(){state->sbEndClosed();}
void Controller::btnStartPressed(){state->btnStartPressed();}
void Controller::btnStartReleased(){state->btnStartReleased();}
void Controller::btnStopPressed(){state->btnStopPressed();}
void Controller::btnStopReleased(){state->btnStopReleased();}
void Controller::btnResetPressed(){state->btnResetPressed();}
void Controller::btnResetReleased(){state->btnResetReleased();}
void Controller::btnEstopPressed(){state->btnEstopPressed();}
void Controller::btnEstopReleased(){state->btnEstopReleased();}

void Controller::setFirstElementInSegment(bool isFirst) {
	firstElementInSegment = isFirst;
}

bool Controller::isFirstElementInSegment() {
	return firstElementInSegment;
}
