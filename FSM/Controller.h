/**
 * SE2 WiSe 2012
 * Controller
 *
 * Each puck on the band conveyor is an object of this class.
 *
 * @file Controller.h
 * @author Chris Addo
 *         Jens Eberwein
 *         Tristan Rudat
 *         Martin Slowikowski
 * @date 2012-11-28
 * @version 0.4
 *
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "CallInterface.h"
class BaseState;
#include <stdio.h>
#include "puckTypes.h"
#include "bandselection.h"

class Controller: public CallInterface {
public:
	Controller(int id);

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

	void setFirstElementInSegment(bool isFirst);
	bool isFirstElementInSegment();

	int getID();
	bool isActive();
	void activate();
	void resetController();

	virtual ~Controller();
	int puckType;


private:
	int id;
	BaseState* state;
	bool firstElementInSegment;

	bool active;
	bool inUse;
};

#endif /* CONTROLLER_H_ */
