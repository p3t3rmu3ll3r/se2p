/*
 * State3.h
 *
 *  Created on: 24.11.2012
 *      Author: martin
 */

#ifndef STATE3_H_
#define STATE3_H_

#include "BaseState.h"

class State3: public BaseState {
public:
	State3(Controller* controller);
	void sbHeightcontrolClosed();
	virtual ~State3();
};

#endif /* STATE3_H_ */
