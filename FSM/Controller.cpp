/*
 * Controller.cpp
 *
 *  Created on: 21.11.2012
 *      Author: aay973
 */

#include "Controller.h"
#include "B1S01_Entry.h"
#include "B2S01_Entry.h"

Controller::Controller(int id) {
	resetController();
	this->id = id;
}

Controller::~Controller() {

}

int Controller::getID(){
	return id;
}

bool Controller::isActive() {
	return active;
}

void Controller::activate() {
	active = true;
}

void Controller::resetController() {
	active = false;
	inUse = false;
	puckType = -1;
	firstElementInSegment = false;
	//state = new BaseState();
}

void Controller::sbStartOpen() {
	if(active && !inUse){
		inUse = true;
#ifdef BAND_1
		state = new B1S01_Entry(this);
#else
		state = new B2S01_Entry(this);
#endif
		state->sbStartOpen();
	}
}


void Controller::sbStartClosed() {
	if(active && inUse){
		state->sbStartClosed();
	}
}

void Controller::sbHeightcontrolOpen() {
	if(active && inUse){
		state->sbHeightcontrolOpen();
	}
}

void Controller::sbHeightcontrolClosed() {
	if(active && inUse){
		state->sbHeightcontrolClosed();
	}
}

void Controller::sbGateOpen() {
	if(active && inUse){
		state->sbGateOpen();
	}
}

void Controller::sbGateClosed() {
	if(active && inUse){
		state->sbGateClosed();
	}
}

void Controller::msMetalTrue() {
	if(active && inUse){
		state->msMetalTrue();
	}
}

void Controller::sbSlideOpen() {
	if(active && inUse){
		state->sbSlideOpen();
	}
}

void Controller::sbSlideClosed() {
	if(active && inUse){
	state->sbSlideClosed();
	}
}

void Controller::sbEndOpen() {
	if(active && inUse){
		state->sbEndOpen();
	}
}

void Controller::sbEndClosed() {
	if(active && inUse){
		state->sbEndClosed();
	}
}

void Controller::btnStartPressed() {
	if(active && inUse){
		state->btnStartPressed();
	}
}

void Controller::btnStartReleased() {
	if(active && inUse){
		state->btnStartReleased();
	}
}

void Controller::btnStopPressed() {
	if(active && inUse){
		state->btnStopPressed();
	}
}

void Controller::btnStopReleased() {
	if(active && inUse){
		state->btnStopReleased();
	}
}

void Controller::btnResetPressed() {
	if(active && inUse){
		state->btnResetPressed();
	}
}

void Controller::btnResetReleased() {
	if(active && inUse){
		state->btnResetReleased();
	}
}

void Controller::btnEstopPressed() {
	if(active && inUse){
		state->btnEstopPressed();
	}
}

void Controller::btnEstopReleased() {
	if(active && inUse){
		state->btnEstopReleased();
	}
}

void Controller::setFirstElementInSegment(bool isFirst) {
	firstElementInSegment = isFirst;
}

bool Controller::isFirstElementInSegment() {
	return firstElementInSegment;
}
