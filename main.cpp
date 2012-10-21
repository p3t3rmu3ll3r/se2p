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

	HALTest halTest;
	halTest.testHal();

	return EXIT_SUCCESS;
}
