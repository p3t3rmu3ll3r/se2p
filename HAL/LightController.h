#ifndef LIGHTCONTROLLER_H_
#define LIGHTCONTROLLER_H_

#include <iostream>
#include "HWaccess.h"
#include "HAWThread.h"
#include "ActorHAL.h"

class LightController: public thread::HAWThread {
public:
	static LightController* getInstance();
	void execute(void*);
	void shutdown();
	virtual ~LightController();

	void operatingNormal();
	void manualTurnover();
	void upcomingNotReceipted();
	void upcomingReceipted();
	void goneUnreceipted();
	void lightsOff();
private:
	void off();
	LightController();
	static LightController *instance;
	void (LightController::*function)(void);
	ActorHAL *aHal;
	void blinkYellow();
	void blinkRedFast();
	void blinkRedSlow();
};
#endif /* LIGHTCONTROLLER_H_ */
