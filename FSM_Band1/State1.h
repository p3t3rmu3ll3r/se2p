/*
 * State1.h
 *
 *  Created on: 24.11.2012
 *      Author: martin
 */

#ifndef STATE1_H_
#define STATE1_H_

#include "BaseState.h"
#include "State2.h"

class State1: public BaseState {
public:
	State1(Controller* controller);

	void sbStartOpen();
	void sbStartClosed();

	virtual ~State1();
};

#endif /* STATE1_H_ */
