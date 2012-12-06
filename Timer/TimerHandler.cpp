/*
 * TimerHandler.cpp
 *
 *  Created on: 05.12.2012
 *      Author: aba079
 */

#include "TimerHandler.h"

TimerHandler* TimerHandler::instance = NULL;
Mutex* TimerHandler::instanceMutex = new Mutex();

TimerHandler::TimerHandler() {
	mutex = new Mutex();
}

TimerHandler::~TimerHandler() {
	if (instance != NULL) {
		delete instance;
		instance = NULL;
		instanceMutex->~Mutex();
	}
}

TimerHandler* TimerHandler::getInstance()
{
	if (!instance) {
		instanceMutex->lock();
		if (!instance) {
			instance = new TimerHandler;
#ifdef DEBUG_TimerHandler
			printf("Debug TimerHandler: New TimerHandler instance created\n");
#endif
		}
		instanceMutex->unlock();
	}
	return instance;
}

Timer* TimerHandler::createTimer(int chid, int sec, int msec, int msg) {
	Timer* tmpTimer = new Timer(chid, sec, msec, msg);
	mutex->lock();
	timers.push_back(tmpTimer);
	mutex->unlock();
	return tmpTimer;
}

void TimerHandler::deleteTimer(Timer* timer) {
	mutex->lock();
	if (!timers.empty()) {
		timer->stop();
		for (uint32_t i = 0; i < timers.size(); i++) {
			if (timers.at(i) == timer) { //TODO: should be safe if called twice, right?!
				timers.erase(timers.begin() + i);
				break;
			}
		}
		delete timer;
		timer = NULL;
	}
	mutex->unlock();
}

void TimerHandler::pauseAllTimers(){
	mutex->lock();
	if (!timers.empty()) {
		for (uint32_t i = 0; i < timers.size(); i++) {
			timers.at(i)->pause();
		}
	}
	mutex->unlock();
}

void TimerHandler::continueAllTimers(){
	mutex->lock();
	if (!timers.empty()) {
		for (uint32_t i = 0; i < timers.size(); i++) {
			timers.at(i)->cont();
		}
	}
	mutex->unlock();
}

