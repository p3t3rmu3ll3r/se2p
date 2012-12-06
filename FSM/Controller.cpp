/**
 * SE2 WiSe 2012
 * Controller
 *
 * Each puck on the band conveyor is an object of this class.
 *
 * @file Controller.h
 * @author Chris Addo
 *         Jens Eberwein
 *         Tristan Rudat
 *         Martin Slowikowski
 * @date 2012-11-28
 * @version 0.4
 *
 */

#include "Controller.h"
#include "B1S01_Entry.h"
#include "B2S01_Entry.h"
#include "State_Test01_Entry.h"

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
	startable = true;
	band1Waiting = false;
	puckType = -1;
	firstElementInSegment = false;
	//state = new BaseState();
}

void Controller::sbStartOpen() {
	if(active && startable){
		startable = false;
#ifdef BAND_1
		state = new B1S01_Entry(this);
#endif
#ifdef BAND_2
		state = new B2S01_Entry(this);
#endif
#ifdef BAND_TEST
		state = new State_Test01_Entry(this);
#endif
		state->sbStartOpen();
	}
}


void Controller::sbStartClosed() {
	if(active){
		state->sbStartClosed();
	}
}

void Controller::sbHeightcontrolOpen() {
	if(active){
		state->sbHeightcontrolOpen();
	}
}

void Controller::sbHeightcontrolClosed() {
	if(active){
		state->sbHeightcontrolClosed();
	}
}

void Controller::sbGateOpen() {
	if(active){
		state->sbGateOpen();
	}
}

void Controller::sbGateClosed() {
	if(active){
		state->sbGateClosed();
	}
}

void Controller::msMetalTrue() {
	if(active){
		state->msMetalTrue();
	}
}

void Controller::sbSlideOpen() {
	if(active){
		state->sbSlideOpen();
	}
}

void Controller::sbSlideClosed() {
	if(active){
	state->sbSlideClosed();
	}
}

void Controller::sbEndOpen() {
	if(active){
		state->sbEndOpen();
	}
}

void Controller::sbEndClosed() {
	if(active){
		state->sbEndClosed();
	}
}

void Controller::btnStartPressed() {
	if(active){
		state->btnStartPressed();
	}
}

void Controller::btnStartReleased() {
	if(active){
		state->btnStartReleased();
	}
}

void Controller::btnStopPressed() {
	if(active){
		state->btnStopPressed();
	}
}

void Controller::btnStopReleased() {
	if(active){
		state->btnStopReleased();
	}
}

void Controller::btnResetPressed() {
	if(active){
		state->btnResetPressed();
	}
}

void Controller::btnResetReleased() {
	if(active){
		state->btnResetReleased();
	}
}

void Controller::btnEstopPressed() {
	if(active){
		state->btnEstopPressed();
	}
}

void Controller::btnEstopReleased() {
	if(active){
		state->btnEstopReleased();
	}
}

void Controller::rs232Band2Ready(){
	if(active){
		state->rs232Band2Ready();
	}
}

void Controller::rs232Band2Ack(){
	if(active){
		state->rs232Band2Ack();
	}
}

void Controller::rs232Band1Waiting(){
	if(active){
#ifdef BAND_2
		band1Waiting = true;
#endif
		state->rs232Band1Waiting();
	}
}

void Controller::timerGateClose(){
	if(active){
		state->timerGateClose();
	}
}
void Controller::timerSlideFull(){
	if(active){
		state->timerSlideFull();
	}
}

void Controller::timerSeg1Min(){
	if(active){
		state->timerSeg1Min();
	}
}
void Controller::timerSeg1Max(){
	if(active){
		state->timerSeg1Max();
	}
}
void Controller::timerSeg2Min(){
	if(active){
		state->timerSeg2Min();
	}
}
void Controller::timerSeg2Max(){
	if(active){
		state->timerSeg2Max();
	}
}
void Controller::timerSeg3Min(){
	if(active){
		state->timerSeg3Min();
	}
}
void Controller::timerSeg3Max(){
	if(active){
		state->timerSeg3Max();
	}
}

void Controller::setFirstElementInSegment(bool isFirst) {
	firstElementInSegment = isFirst;
}

bool Controller::isFirstElementInSegment() {
	return firstElementInSegment;
}

bool Controller::isBand1Waiting(){
	return band1Waiting;
}

void Controller::setSegTimerMinCalled(bool boolean){
	segTimerMinCalled = boolean;
}

bool Controller::isSegTimerMinCalled(){
	return segTimerMinCalled;
}

void Controller::resetSegTimers(){
	setSegTimerMinCalled(false);
	TimerHandler::getInstance()->deleteTimer(segTimerMin);
	TimerHandler::getInstance()->deleteTimer(segTimerMax);
}
