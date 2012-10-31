/**
 * SE2 WiSe 2012
 * main class
 *
 * @file main.cpp
 * @author Chris Addo
 *         Jens Eberwein
 *         Tristan Rudat
 *         Martin Slowikowski
 * @date 2012-10-23
 * @version 0.2
 * 
 */

#include <cstdlib>
#include <iostream>
#include <unistd.h>

#include "Tests/HALTest.h"
#include "Tests/RS232Test.h"
#include "LightController.h"
#include "Tests/LightControllerTest.h"
#include "Sensor.h"



int main(int argc, char *argv[]) {

	//MyObject* myObject = new MyObject();
	//myObject->myMethod();
	//delete myObject;

	//thread::MyThread thread;
	//thread.start(NULL);

	//Testing Milestone 2
	//HALTest halTest;
	//halTest.testHal();

	//RS232Test rs232Test;
	//rs232Test.testRS232();

	// Testing Milestone 3
	//LightController* lc = LightController::getInstance();
	//lc->start(0);
	//lc->hold();
	//LightControllerTest lctest;
	//lctest.testLightController();

	Sensor sensor;
	int i = sensor.getHeight();
	printf("Krass hoch: %d\n", i);
	//int coid = ConnectAttach(0, 0, sensor.getChid(), _NTO_SIDE_CHANNEL, 0);
	struct _pulse pulse;
	int rc = MsgReceivePulse(sensor.getChid(), &pulse, sizeof(pulse), NULL);
	if(rc < 0) {
		printf("Error in recv pulse\n");
	}

	if(pulse.code == 5) {
		printf("Pulse from ISR rcved\n");
	}
	printf("ISR status: %x\n", pulse.value.sival_int);

	return EXIT_SUCCESS;
}
