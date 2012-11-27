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

#include "ISRHandler.h"
#include "PuckHandler.h"
#include "Controller.h"
#include "ErrorFSM.h"

#define BAND_1

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
	//LightControllerTest lctest;
	//lctest.testLightController();

	//ISRTest isrtest;
	//isrtest.start(0);

	//weil wichtig fuer sim ioacces_open
	ActorHAL::getInstance();
	SensorHAL::getInstance();

	ErrorFSM* errfsm = ErrorFSM::getInstance();
	errfsm->start(0);

	Dispatcher* disp = Dispatcher::getInstance();
	disp->start(0);



	ISRHandler::getInstance()->start(0);
	PuckHandler::getInstance()->initializePucks(disp);


	char breakWhile = 0;
	while(1){
		//tastatureiongabe lesen, dann thread stoppen, irqs stoppen, join, profit
		std::cin >> breakWhile;
		if(breakWhile == 'q'){
			break;
		}
	}

	//TODO testen, ob das kombinierte stop() aus ISRTest geht!
	//isrtest.stop();
	//SensorHAL::getInstance()->stopInterrupt();
	//isrtest.join();

	printf("EXIT_SUCCESS \n");

	return EXIT_SUCCESS;
}
