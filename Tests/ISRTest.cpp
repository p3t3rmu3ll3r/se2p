/*
 * ISRTest.cpp
 *
 *  Created on: 29.10.2012
 *      Author: martin
 */

#include "ISRTest.h"

ISRTest::ISRTest() {
	// TODO Auto-generated constructor stub

}

ISRTest::~ISRTest() {
	// TODO Auto-generated destructor stub
}

void ISRTest::execute(void*) {
	while (!isStopped()) {
		//do time consuming stuff
	}
}

void ISRTest::shutdown() {
}
