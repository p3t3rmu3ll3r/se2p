/*
 * B1S08_End.h
 *
 *  Created on: 25.11.2012
 *      Author: martin
 */

#ifndef B1S08_END_H_
#define B1S08_END_H_

#include "BaseState.h"

class B1S08_End: public BaseState {
public:
	B1S08_End(Controller* controller);
	virtual ~B1S08_End();

	void sbEndClosed();
};

#endif /* B1S08_END_H_ */
