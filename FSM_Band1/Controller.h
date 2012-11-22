/*
 * Controller.h
 *
 *  Created on: 21.11.2012
 *      Author: aay973
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "CallInterface.h"
#include "BaseState.h"
#include <stdio.h>

class Controller: public CallInterface {
public:
	Controller();

	void sbStartOpen();
	void sbStartClosed();
	void sbHeightcontrolOpen();
	void sbHeightcontrolClosed();
	void sbGateOpen();
	void sbGateClosed();
	void msMetalTrue();
	void sbSlideOpen();
	void sbSlideClosed();
	void sbEndOpen();
	void sbEndClosed();
	void btnStartPressed();
	void btnStartReleased();
	void btnStopPressed();
	void btnStopReleased();
	void btnResetPressed();
	void btnResetReleased();
	void btnEstopPressed();
	void btnEstopReleased();

	virtual ~Controller();

private:
	BaseState state;
};

#endif /* CONTROLLER_H_ */
