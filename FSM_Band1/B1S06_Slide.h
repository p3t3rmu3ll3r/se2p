/*
 * B1S06_Slide.h
 *
 *  Created on: 25.11.2012
 *      Author: martin
 */

#ifndef B1S06_SLIDE_H_
#define B1S06_SLIDE_H_

#include "BaseState.h"

class B1S06_Slide: public BaseState {
public:
	B1S06_Slide(Controller* controller);
	virtual ~B1S06_Slide();

	void sbSlideClosed();
};

#endif /* B1S06_SLIDE_H_ */
