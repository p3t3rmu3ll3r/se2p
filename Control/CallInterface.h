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
	virtual void sbStartOpen()=0;
	virtual void sbStartClosed()=0;
	virtual void sbHeightcontrolOpen()=0;
	virtual void sbHeightcontrolClosed()=0;
	virtual void sbGateOpen()=0;
	virtual void sbGateClosed()=0;
	virtual void msMetalTrue()=0;
	virtual void sbSlideOpen()=0;
	virtual void sbSlideClosed()=0;
	virtual void sbEndOpen()=0;
	virtual void sbEndClosed()=0;
	virtual void btnStartPressed()=0;
	virtual void btnStartReleased()=0;
	virtual void btnStopPressed()=0;
	virtual void btnStopReleased()=0;
	virtual void btnResetPressed()=0;
	virtual void btnResetReleased()=0;
	virtual void btnEstopPressed()=0;
	virtual void btnEstopReleased()=0;
};

#endif /* CALLINTERFACE_H_ */
