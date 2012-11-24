/*
 * State2.h
 *
 *  Created on: 24.11.2012
 *      Author: martin
 */

#ifndef STATE2_H_
#define STATE2_H_

#include "BaseState.h"
#include "State3.h"

class State2: public BaseState {
public:
	State2(Controller* controller);
	void sbHeightcontrolOpen();
	virtual ~State2();
};

#endif /* STATE2_H_ */
