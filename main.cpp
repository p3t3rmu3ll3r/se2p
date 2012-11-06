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
#include <stdio.h>

#include "Tests/HALTest.h"
#include "Tests/RS232Test.h"
#include "LightController.h"
#include "Tests/LightControllerTest.h"
#include "SensorHAL.h"
#include "ISRTest.h"



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
	//lc->stop();
	//lc->join();

	// ISR Test
	ISRTest isrtest;
	isrtest.start(0);

	char breakWhile = 0;
	while(1){
		//tastatureiongabe lesen, dann thread stoppen, irqs stoppen, join, profit
		std::cin >> breakWhile;
		if(breakWhile == 'q'){
			break;
		}
	}

	//TODO testen, ob das kombinierte stop() aus ISRTest geht!
	isrtest.stop();
	//SensorHAL::getInstance()->stopInterrupt();
	isrtest.join();

	return EXIT_SUCCESS;
}
