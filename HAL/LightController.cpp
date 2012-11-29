/**
 * SE2 WiSe 2012
 * LightController for the traffic lights
 *
 * Offers functions for different states the festo
 * system can have. Running in a Thread. Status of
 * the traffic light is manipulated through public
 * accessible functions.
 *
 * @file LightController.cpp
 * @author Chris Addo
 * Jens Eberwein
 * Tristan Rudat
 * Martin Slowikowski
 * @date 2012-10-29
 * @version 0.4
 *
 */

#include "LightController.h"

LightController* LightController::instance = NULL;
Mutex* LightController::lightInstanceMutex = new Mutex();

LightController::LightController() {
	aHal = ActorHAL::getInstance();

	function = &LightController::off;
	start(0);
	hold();
}

LightController::~LightController() {
	if (instance != NULL) {
		delete instance;
		instance = NULL;
		lightInstanceMutex->~Mutex();
	}
}

LightController* LightController::getInstance() {
	if (!instance) {
		lightInstanceMutex->lock();
		if (!instance) {
			instance = new LightController();
#ifdef DEBUG_LIGHTCONTROLLER
			printf("Debug LightController: New LC instance created\n");
#endif
		}
		lightInstanceMutex->unlock();
	}

	return instance;
}

void LightController::execute(void*) {
	while (!isStopped()) {
		(this->*function)();
	}
}

void LightController::shutdown() {
}

void LightController::operatingNormal() {
	lightsOff();
	aHal->lightGreen(true);
}

void LightController::ledStart(bool isOn) {
	if(isOn){
		aHal->ledStart(true);
	} else {
		aHal->ledStart(false);
	}
}

void LightController::ledReset(bool isOn) {
	if(isOn){
		aHal->ledReset(true);
	} else {
		aHal->ledReset(false);
	}
}

void LightController::manualTurnover() {
	lightsOff();
	function = &LightController::blinkYellow;
	cont();
}

void LightController::upcomingNotReceipted() {
	lightsOff();
	function = &LightController::blinkRedSlow;
	cont();
}

void LightController::upcomingReceipted() {
	lightsOff();
	aHal->lightRed(true);
}

void LightController::goneUnreceipted() {
	lightsOff();
	function = &LightController::blinkRedFast;
	cont();
}

void LightController::bandHalted() {
	lightsOff();
	function = &LightController::blinkGreenFast;
	cont();
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

void LightController::blinkGreenFast() {
	aHal->lightGreen(true);
	usleep(500000);
	aHal->lightGreen(false);
	usleep(500000);
}

void LightController::blinkRedSlow() {
	aHal->lightRed(true);
	usleep(500000);
	aHal->lightRed(false);
	usleep(500000);
}

void LightController::lightsOff() {
	aHal->lightsOff();
	off();
}

void LightController::off() {
	hold();
}
