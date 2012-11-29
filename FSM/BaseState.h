/**
 * SE2 WiSe 2012
 * BaseState
 *
 * Represents a state in the used state pattern. All used states
 * are derived from this class.
 *
 * @file BaseState.h
 * @author Chris Addo
 *         Jens Eberwein
 *         Tristan Rudat
 *         Martin Slowikowski
 * @date 2012-11-22
 * @version 0.1
 *
 */

#ifndef BASESTATE_H_
#define BASESTATE_H_

#include <stdio.h>
#include "CallInterface.h"
#include "PuckHandler.h"
#include "ActorHAL.h"
#include "SensorHAL.h"
#include "ErrorFSM.h"

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
	SensorHAL* sensorHAL;
	PuckHandler* puckHandler;
	Controller* controller;
	ErrorFSM* errfsm;
};

#endif /* BASESTATE_H_ */
