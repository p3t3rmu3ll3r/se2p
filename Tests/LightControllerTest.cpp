/**
 * SE2 WiSe 2012
 * LightController test
 *
 * Offers functions for different states the festo
 * system can have. Running in a Thread. Status of
 * the traffic light is manipulated through public
 * accessible functions.
 *
 * \file LightControllerTest.cpp
 * \author Chris Addo
 *         Jens Eberwein
 *         Tristan Rudat
 *         Martin Slowikowski
 * \date 2012-10-29
 * \version 0.1
 *
 */

#include "LightControllerTest.h"

LightControllerTest::LightControllerTest() {

}

LightControllerTest::~LightControllerTest() {
}

void LightControllerTest::testLightController() {

	LightController* lc = LightController::getInstance();

	lc->start(NULL);
	sleep(3);
	lc->operatingNormal();
	sleep(5);
	lc->upcomingNotReceipted();
	sleep(5);
	lc->upcomingReceipted();
	sleep(5);
	lc->goneUnreceipted();
	sleep(5);
	lc->manualTurnover();
	sleep(5);
	lc->lightsOff();
}
