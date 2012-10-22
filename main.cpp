/**
 * SE2 WiSe 2012
 * main class
 *
 * Some bla bla bla for this file
 * 
 * @file main.cpp
 * @author Chris Addo
 *         Jens Eberwein
 *         Tristan Rudat
 *         Martin Slowikowski
 * @date 2012-10-18
 * @version 0.1
 * 
 */

#include <cstdlib>
#include <iostream>
#include <unistd.h>

#include "MyThread.h"

#include "HAL/HAL.h"
#include "Tests/HALTest.h"
#include "AmpelTest.h"
#include "RS232.h"

int main(int argc, char *argv[]) {

	//MyObject* myObject = new MyObject();
	//myObject->myMethod();
	//delete myObject;

/*
	AmpelTest test;
	test.ampeltest();
*/

	//thread::MyThread thread;
	//thread.start(NULL);


	//HAL* hal = HAL::getInstance();
	RS232* com = RS232::getInstance();
	com->start(NULL);
	sleep(10);
	com->stop();
	sleep(3);
	com->sendMsg('a');
	com->join();
	//HALTest halTest;
	//halTest.testHal();

	/*
	hal->engineRight(false);
	sleep(3);
	hal->engineRight(true);
	sleep(3);
	hal->engineRight(false);
	sleep(3);
	hal->engineStop();
	sleep(3);
	hal->engineUnstop();
	sleep(3);
	hal->engineStop();
    */


	return EXIT_SUCCESS;
}
