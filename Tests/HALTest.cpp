/*
 * HALTest.cpp
 *
 *  Created on: 21.10.2012
 *      Author: martin
 */

#include "HALTest.h"

HALTest::HALTest() {
	// TODO Auto-generated constructor stub

}

HALTest::~HALTest() {
	// TODO Auto-generated destructor stub
}

void HALTest::testHal()
{
	HAL* hal = HAL::getInstance();
	// Lights
	hal->lightRed(true);
	sleep(1);
	hal->lightRed(false);
	sleep(1);

	hal->lightYellow(true);
	sleep(1);
	hal->lightYellow(false);
	sleep(1);

	hal->lightRed(true);
	sleep(1);
	hal->lightRed(false);
	sleep(1);

	// Engine
	hal->engineRight(false);
	sleep(5);
	hal->engineRight(true);
	sleep(5);
	hal->engineStop();
	sleep(5);
	hal->engineUnstop();
	sleep(5);
	hal->engineStop();

	// Weiche
	hal->gate(true);
	sleep(3);
	hal->gate(false);
	sleep(1);

	// LEDs
	hal->ledStart(true);
	hal->ledReset(true);
	hal->ledQ1(true);
	hal->ledQ2(true);
	sleep(5);
	hal->ledStart(false);
	hal->ledReset(false);
	hal->ledQ1(false);
	hal->ledQ2(false);
	sleep(1);
}
