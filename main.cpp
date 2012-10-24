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

#include "MyThread.h"

#include "Tests/HALTest.h"
#include "Tests/RS232Test.h"


int main(int argc, char *argv[]) {

	//MyObject* myObject = new MyObject();
	//myObject->myMethod();
	//delete myObject;

	//thread::MyThread thread;
	//thread.start(NULL);

	//Testing Milestone 2
	//HALTest halTest;
	//halTest.testHal();

	RS232Test rs232Test;
	rs232Test.testRS232();

	return EXIT_SUCCESS;
}
