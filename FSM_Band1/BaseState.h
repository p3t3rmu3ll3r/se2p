/*
 * BaseState.h
 *
 *  Created on: 21.11.2012
 *      Author: aay973
 */

#ifndef BASESTATE_H_
#define BASESTATE_H_

#include <stdio.h>
#include "CallInterface.h"
#include "PuckHandler.h"
#include "ActorHAL.h"

class BaseState: public CallInterface {
public:
	BaseState();

	virtual void sbStartOpen();
	virtual void sbStartClosed();
	virtual void sbHeightcontrolOpen();
	virtual void sbHeightcontrolClosed();
	virtual void sbGateOpen();
	virtual void sbGateClosed();
	virtual void msMetalTrue();
	virtual void sbSlideOpen();
	virtual void sbSlideClosed();
	virtual void sbEndOpen();
	virtual void sbEndClosed();
	virtual void btnStartPressed();
	virtual void btnStartReleased();
	virtual void btnStopPressed();
	virtual void btnStopReleased();
	virtual void btnResetPressed();
	virtual void btnResetReleased();
	virtual void btnEstopPressed();
	virtual void btnEstopReleased();

	virtual ~BaseState();

protected:
	ActorHAL* actorHAL;
	PuckHandler* puckHandler;
	Controller* controller;
};

#endif /* BASESTATE_H_ */
