/*
 * messages.h
 *
 *  Created on: 17.11.2012
 *      Author: martin
 */

#ifndef CALLINTERFACE_H_
#define CALLINTERFACE_H_

// ISR Handler pulse messages

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
