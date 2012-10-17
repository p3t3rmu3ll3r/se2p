#include <cstdlib>
#include <iostream>
#include <unistd.h>

#include "MyObject.h"
#include "MyThread.h"
#include "AmpelTest.h"

using namespace thread;

int main(int argc, char *argv[]) {
	std::cout << "Welcome to the QNX Momentics IDE" << std::endl;

	MyObject* myObject = new MyObject();
	myObject->myMethod();
	delete myObject;

	AmpelTest test;
	test.ampeltest();

	MyThread thread;
	thread.start(NULL);

	sleep(10);

	thread.stop();
	thread.join();

	return EXIT_SUCCESS;
}
