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

LightController* LightController::instance = NULL;
Mutex* LightController::lightInstanceMutex = new Mutex();

LightController::LightController() {
	hal = HAL::getInstance();

	function = &LightController::lightsOff;
	//start(0);
	//hold();
}

LightController::~LightController() {
	delete instance;
	instance = NULL;
	lightInstanceMutex->~Mutex();
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
		sleep(1);
	while (!isStopped()) {
		(this->*function)();
	}
}

void LightController::shutdown() {
}

void LightController::operatingNormal() {
	lightsOff();
	hal->lightGreen(true);
}

void LightController::manualTurnover() {
	hold();
	lightsOff();
	function = &LightController::blinkYellow;
	cont();
}

void LightController::upcomingNotReceipted() {
	hold();
	lightsOff();
	function = &LightController::blinkRedSlow;
	cont();
}

void LightController::upcomingReceipted() {
	hold();
	lightsOff();
	hal->lightRed(true);
}

void LightController::goneUnreceipted() {
	hold();
	lightsOff();
	function = &LightController::blinkRedFast;
	cont();
}

void LightController::blinkYellow() {
	hal->lightYellow(true);
	sleep(1);
	hal->lightYellow(false);
	sleep(1);
}

void LightController::blinkRedFast() {
	hal->lightRed(true);
	sleep(1);
	hal->lightRed(false);
	sleep(1);
}

void LightController::blinkRedSlow() {
	hal->lightRed(true);
	usleep(500000);
	hal->lightRed(false);
	usleep(500000);
}

void LightController::lightsOff() {
	hal->lightsOff();
	hold();
}
