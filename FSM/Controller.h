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
	/**
	 * Parameterized constructor for a Controller
	 *
	 * @param id [1-12]
	 */
	Controller(int id);

	/**
	 * Controller is derived from CallInterface, these functions
	 * are already documented there
	 */
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

	/**
	 * Each controller (puck) is held in a specific queue. For each
	 * segment there are queues. If a puck is the first one in its segment,
	 * corresponding bool is set. Function to determine, whether if puck is
	 * first or not is in the PuckHandler.
	 *
	 * @param isFirst [true if yes, else false]
	 */
	void setFirstElementInSegment(bool isFirst);

	/**
	 * Returns whether puck is first in segment or not
	 *
	 * @return [true if yes, else false]
	 */
	bool isFirstElementInSegment();

	/**
	 * Returns ID of this controller (puck)
	 *
	 * @return controller id
	 */
	int getID();

	/**
	 * Return if this controller (puck) is activated or not.
	 * It means if this puck is actually lying on the band
	 * conveyor
	 *
	 * @return active [true if yes, else false]
	 */
	bool isActive();

	/**
	 * Activates a controller (puck), if it is placed on the band
	 * conveyor
	 */
	void activate();

	/**
	 * Resets the controller (puck) to its start values.
	 * If controller (puck) is being removed from the band
	 * conveyor it needs to be resetted, so it can be activated
	 * for a new puck being placed on the band conveyor.
	 */
	void resetController();

	/**
	 * Empty standard destructor
	 */
	virtual ~Controller();

	/**
	 * Type of the puck, valid types are defined in puckTypes.h
	 */
	int puckType;


private:
	/**
	 * Corresponding id of this controller (puck), can be number between
	 * 1 and MAX_PUCKS_BAND (defined in PuckHandler.h)
	 */
	int id;

	/**
	 * Each controller can be in a state derived or from type BaseState.
	 */
	BaseState* state;

	/**
	 * If controller (puck) is first element in its segment true, else false.
	 */
	bool firstElementInSegment;

	/**
	 * If a puck is placed on band conveyor, the Dispatcher activates a puck
	 * through the PuckHandler.
	 * [false if not in use and not on band conveyor, true if placed on conveyor]
	 */
	bool active;

	/**
	 * A puck is in use, if it was activated and got the dispatched signal
	 * sbStartOpen(). inUse is set to true. Otherwise everytime the signal
	 * is issued again (new puck on band) the state would be reset!
	 */
	bool inUse;
};

#endif /* CONTROLLER_H_ */
