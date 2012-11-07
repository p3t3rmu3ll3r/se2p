/**
 * SE2 WiSe 2012
 * LightController for the traffic lights
 *
 * Offers functions for different states the festo
 * system can have. Running in a Thread. Status of
 * the traffic light is manipulated through public
 * accessible functions.
 *
 * \file LightController.cpp
 * \author Chris Addo
 *         Jens Eberwein
 *         Tristan Rudat
 *         Martin Slowikowski
 * \date 2012-10-29
 * \version 0.4
 *
 */

#include "LightController.h"
LightController *LightController::instance = 0;
LightController *LightController::getInstance() {
	if (instance == 0) {
		instance = new LightController();
	}
	return instance;
}
LightController::LightController() {
	aHal = ActorHAL::getInstance();
	function = &LightController::off;
	start(0);
	hold();
}
LightController::~LightController() {
}
void LightController::execute(void*) {
	while (!isStopped()) {
		(this->*function)();
	}
}
void LightController::shutdown() {
}
void LightController::changeState(State state) {
	switch (state) {
	case MANUAL_TURNOVER:
		function = &LightController::blinkYellow;
		break;
	case UPCOMING_NOT_RECEIPTED:
		function = &LightController::blinkRedSlow;
		break;
	case GONE_UNRECEIPTED:
		function = &LightController::blinkRedFast;
		break;
	default:
		stop();
	}
}
void LightController::stopBlinker() {
	hold();
}
void LightController::operatingNormal() {
	stopBlinker();
	aHal->lightsOff();
	aHal->lightGreen(true);
}
void LightController::manualTurnover() {
	stopBlinker();
	aHal->lightsOff();
	changeState(MANUAL_TURNOVER);
	cont();
}
void LightController::upcomingNotReceipted() {
	stopBlinker();
	aHal->lightsOff();
	changeState(UPCOMING_NOT_RECEIPTED);
	cont();
}
void LightController::upcomingReceipted(){
	stopBlinker();
	aHal->lightsOff();
	aHal->lightRed(true);
}
void LightController::goneUnreceipted(){
	stopBlinker();
	aHal->lightsOff();
	changeState(GONE_UNRECEIPTED);
	cont();
}
void LightController::lightsOff() {
	aHal->lightsOff();
	off();
}
void LightController::off() {
	hold();
}
void LightController::blinkYellow() {
	aHal->lightYellow(true);
	sleep(1);
	aHal->lightYellow(false);
	sleep(1);
}
void LightController::blinkRedFast() {
	aHal->lightRed(true);
	sleep(1);
	aHal->lightRed(false);
	sleep(1);
}
void LightController::blinkRedSlow() {
	aHal->lightRed(true);
	usleep(500000);
	aHal->lightRed(false);
	usleep(500000);
}
