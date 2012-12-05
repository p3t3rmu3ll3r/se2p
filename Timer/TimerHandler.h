/*
 * TimerHandler.h
 *
 *  Created on: 05.12.2012
 *      Author: aba079
 */

#ifndef TIMERHANDLER_H_
#define TIMERHANDLER_H_

#include <vector>
#include <iostream.h>
#include <stdint.h>
#include "Timer.h"
#include "Mutex.h"

#define DEBUG_TimerHandler

class TimerHandler {
public:
	/**
	 * Standard destructor
	 */
	virtual ~TimerHandler();

	/**
	 * Function returns an instance of the TimerHandler-class. Class is
	 * using singleton pattern, so only one instance for access to
	 * TimerHandler exists.
	 * @return instance for TimerHandler
	 */
	static TimerHandler* getInstance();

	/**
	 * TODO
	 */
	Timer* createTimer(int chid, int sec, int msec, int msg);
	void deleteTimer(Timer* timer);
	void pauseAllTimers();
	void continueAllTimers();

private:
	/**
	 * default private constructor for singleton pattern.
	 */
	TimerHandler();

	/**
	 * instance for TimerHandler (singleton)
	 */
	static TimerHandler* instance;

	/**
	 * mutex for securing access to TimerHandler instance
	 */
	static Mutex* instanceMutex;

	/**
	 * TODO
	 */
	vector<Timer*> timers;
	Mutex* mutex;
};

#endif /* TIMERHANDLER_H_ */
