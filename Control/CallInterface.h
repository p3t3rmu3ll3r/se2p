/**
 * SE2 WiSe 2012
 * CallInterface (abstract class)
 *
 * Contains all functions that can be dispatched (from Dispatcher, RS232, ...)
 *
 * @file CallInterface.h
 * @author Chris Addo
 *         Jens Eberwein
 *         Tristan Rudat
 *         Martin Slowikowski
 * @date 2012-11-22
 * @version 0.1
 *
 */

#ifndef CALLINTERFACE_H_
#define CALLINTERFACE_H_

class CallInterface {
public:
	/**
	 * LightBarrier 1 at the beginning of band conveyor is interrupted
	 */
	virtual void sbStartOpen()=0;

	/**
	 * LightBarrier 1 at the beginning of band conveyor is closed
	 */
	virtual void sbStartClosed()=0;

	/**
	 * LightBarrier 2 at the height measurement of band conveyor is interrupted
	 */
	virtual void sbHeightcontrolOpen()=0;

	/**
	 * LightBarrier 2 at the height measurement of band conveyor is closed
	 */
	virtual void sbHeightcontrolClosed()=0;

	/**
	 * LightBarrier 3 at the gate of band conveyor is interrupted
	 */
	virtual void sbGateOpen()=0;

	/**
	 * LightBarrier 3 at the gate of band conveyor is closed
	 */
	virtual void sbGateClosed()=0;

	/**
	 * Puck contains metal
	 */
	virtual void msMetalTrue()=0;

	/**
	 * LightBarrier 4 at the slide of band conveyor is interrupted
	 */
	virtual void sbSlideOpen()=0;

	/**
	 * LightBarrier 4 at the slide of band conveyor is closed
	 */
	virtual void sbSlideClosed()=0;

	/**
	 * LightBarrier 5 at the end of band conveyor is interrupted
	 */
	virtual void sbEndOpen()=0;

	/**
	 * LightBarrier 5 at the end of band conveyor is closed
	 */
	virtual void sbEndClosed()=0;

	/**
	 * Start button at Festo system was pressed
	 */
	virtual void btnStartPressed()=0;

	/**
	 * Start button at Festo system was released
	 */
	virtual void btnStartReleased()=0;

	/**
	 * Stop button at Festo system was pressed
	 */
	virtual void btnStopPressed()=0;

	/**
	 * Stop button at Festo system was released
	 */
	virtual void btnStopReleased()=0;

	/**
	 * Reset button at Festo system was pressed
	 */
	virtual void btnResetPressed()=0;

	/**
	 * Reset button at Festo system was released
	 */
	virtual void btnResetReleased()=0;

	/**
	 * Emergency stop button at Festo system was pressed
	 */
	virtual void btnEstopPressed()=0;

	/**
	 * Emergency stop button at Festo system was released
	 */
	virtual void btnEstopReleased()=0;

	/**
	 * RS232 heartbeat signal, that band2 is still alive
	 */
	virtual void rs232Band2Ack()=0;

	/**
	 * Band2 is ready to receive new puck
	 */
	virtual void rs232Band2Ready()=0;

	/**
	 * Band1 is waiting for band2 to be free
	 */
	virtual void rs232Band1Waiting()=0;
};

#endif /* CALLINTERFACE_H_ */
