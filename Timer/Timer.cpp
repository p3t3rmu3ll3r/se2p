/**
 * SE2 WiSe 2012
 * Timer
 *
 * Timer class for exception and error handling.
 *
 * @file Timer.cpp
 * @author Chris Addo
 *         Jens Eberwein
 *         Tristan Rudat
 *         Martin Slowikowski
 * @date 2012-12-03
 * @version 0.1
 *
 */

#include "Timer.h"

Timer::Timer(int chid, int sec, int msec, int msg) {
	if ((coid = ConnectAttach(0, 0, chid, _NTO_SIDE_CHANNEL, 0)) == -1) {
		printf("Timer: Error in ConnectAttach\n");
	}

	SIGEV_PULSE_INIT(&event, coid, SIGEV_PULSE_PRIO_INHERIT, PULSE_FROM_TIMER, msg/*Timer abgelaufen*/);

	if (timer_create(CLOCK_REALTIME, &event, &timerid) == -1) {
		printf("Timer: Error in timer_create()\n");
	}

	seconds = sec;
	miliSeconds = msec;

	reset();
}

Timer::~Timer() {
	if (ConnectDetach(coid) == -1) {
		printf("Timer: Error in ConnectDetach\n");
	}

	if (timer_delete(timerid) == -1) {
		printf("Timer: Error in timer_delete()\n");
	}
}

void Timer::start() {
	//TODO running flag, wg doppelt pause / continue
	if(timer_settime(timerid, 0, &timer, NULL) == -1){
		printf("Timer: Error in timer_settime()\n");
	}
}

void Timer::stop() {
	// Stoppe den Timer
	if(timer_settime(timerid, 0, NULL, NULL) == -1){
		printf("Timer: Error in timer_settime()\n");
	}

	// Zuruecksetzen
	reset();
}

void Timer::pause() {
	// disarm (da erster Wert NULL)
	if(timer_settime(timerid, 0, NULL, &backupTimer) == -1){
		printf("Timer: Error in timer_settime()\n");
	}
}

void Timer::cont() {
	// Arm, da Werte im struct wieder != 0
	if(timer_settime(timerid, 0, &backupTimer, NULL) == -1) {
		printf("Timer: Error in timer_settime()\n");
	}
}

void Timer::reset(){
	timer.it_value.tv_sec = seconds;
	timer.it_value.tv_nsec = miliSeconds * MILLISECONDS_NANOSECONDS_CONV;
	timer.it_interval.tv_sec = 0;
	timer.it_interval.tv_nsec = 0;
}

void Timer::changeTime(int sec, int msec){
	seconds = sec;
	miliSeconds = msec;
	reset();
}
