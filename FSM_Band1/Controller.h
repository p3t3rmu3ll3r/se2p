/*
 * FSM_Band1.h
 *
 *  Created on: 21.11.2012
 *      Author: aay973
 */

#ifndef FSM_BAND1_H_
#define FSM_BAND1_H_

#include "CallInterface.h"

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

#endif /* FSM_BAND1_H_ */
