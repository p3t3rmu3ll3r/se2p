/*
 * ISRTest.h
 *
 *  Created on: 29.10.2012
 *      Author: martin
 */

#ifndef ISRTEST_H_
#define ISRTEST_H_

#include "HAWThread.h"

class ISRTest : public thread::HAWThread {
public:
	ISRTest();
	virtual ~ISRTest();

	virtual void execute(void* arg);
	virtual void shutdown();
};

#endif /* ISRTEST_H_ */
