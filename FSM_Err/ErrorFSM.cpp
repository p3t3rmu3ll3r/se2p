/*
 * ErrorFSM.cpp
 *
 *  Created on: 26.11.2012
 *      Author: martin
 */

#include "ErrorFSM.h"

ErrorFSM* ErrorFSM::instance = NULL;
Mutex* ErrorFSM::errfsmInstanceMutex = new Mutex();

ErrorFSM::ErrorFSM() {
	state = ERR_STATE_IDLE;
	aHal = ActorHAL::getInstance();
	lc = LightController::getInstance();

	//Create channel for pulse notification
	if ((ownChid = ChannelCreate(0)) == -1) {
		printf("ErrorFSM: Error in ChannelCreate\n");
	}

	if ((replyChid = ChannelCreate(0)) == -1) {
		printf("ErrorFSM: Error in ChannelCreate\n");
	}

	if ((replyCoid = ConnectAttach(0, 0, replyChid, _NTO_SIDE_CHANNEL, 0)) == -1) {
		printf("ErrorFSM: Error in ConnectAttach\n");
	}
}

ErrorFSM::~ErrorFSM() {
	if (instance != NULL) {
		delete instance;
		instance = NULL;
		errfsmInstanceMutex->~Mutex();
	}
}

ErrorFSM* ErrorFSM::getInstance() {
	if (!instance) {
		errfsmInstanceMutex->lock();
		if (!instance) {
			instance = new ErrorFSM;
#ifdef DEBUG_ErrorFSM
			printf("Debug ErrorFSM: New ErrorFSM instance created\n");
#endif
		}
		errfsmInstanceMutex->unlock();
	}

	return instance;
}

void ErrorFSM::execute(void*) {
	int rc;
	struct _pulse pulse;
	int pulseVal;
	int pulseCode;
	bool isSbStartOpen = false;

	lc->operatingNormal();

	while (!isStopped()) {
#ifdef DEBUG_ErrorFSM
		printf("errorfsm before recv\n");
#endif
		rc = MsgReceivePulse(ownChid, &pulse, sizeof(pulse), NULL);
		if (rc < 0) {
			printf("ErrorFSM: Error in recv pulse\n");
			if (isStopped()) {
				break;
			}
		}
		pulseCode = pulse.code;
		pulseVal = pulse.value.sival_int;
#ifdef DEBUG_ErrorFSM
		printf("errorfsm after recv; code: %d, value: %d\n", pulseCode, pulseVal);
#endif

		switch (state) {
		//Bei idle nur auf Pucks hoeren, IRQs interessieren uns nicht ...
		case ERR_STATE_IDLE:
			if (pulseCode == PULSE_FROM_PUCK) {
				//naechsten zustand vorbereiten mit licht band anhalten und so ...
				switch (pulseVal) {
				case ERR_STATE_SLIDE_FULL:
					aHal->engineFullStop();
					lc->upcomingNotReceipted();
					break;
				case ERR_STATE_TURNOVER:
					aHal->engineFullStop();
					lc->manualTurnover();
					break;
				case ERR_STATE_ERROR:
					aHal->engineFullStop();
					lc->upcomingNotReceipted();
					break;
				case ERR_STATE_TURNOVER_BAND2:
					aHal->engineFullStop();
					lc->upcomingNotReceipted();
					break;
				default:
					printf("nop\n");
				}
				// zustand setzen und wieder ab nach oben im recv blocken
				state = pulseVal;
			}
			break;

		case ERR_STATE_SLIDE_FULL:
			if (pulseCode == PULSE_FROM_ISRHANDLER) {
				if (pulseVal == SB_SLIDE_CLOSED) {
					lc->goneUnreceipted();
				} else if (pulseVal == BTN_RESET_PRESSED) {
					lc->upcomingReceipted();
					state = ERR_STATE_SLIDE_FULL_RECEIPTED;
				}
			}
			break;
		case ERR_STATE_SLIDE_FULL_RECEIPTED:
			if (pulseCode == PULSE_FROM_ISRHANDLER) {
				if(pulseVal == BTN_START_PRESSED){
					lc->operatingNormal();
					//msg puck error solved, reihenfolge unstop und msg puck?!
					sendPuckReply();
					aHal->engineFullUnstop();
					state = ERR_STATE_IDLE;
				}
			}
			break;
		case ERR_STATE_TURNOVER:
			//TODO spaeter auch SB_END_CLOSED abfangen mit if und timer starten fuer wartezeit, bis gedreht wird
			if(pulseCode == PULSE_FROM_ISRHANDLER){
				if(pulseVal == SB_END_OPEN){
					lc->operatingNormal();
					//msg puck error solved, reihenfolge unstop und msg puck?!
					sendPuckReply();
					aHal->engineFullUnstop();
					state = ERR_STATE_IDLE;
				}
			}
			break;
		case ERR_STATE_ERROR:
			if(pulseCode == PULSE_FROM_ISRHANDLER){
				if(pulseVal == BTN_RESET_PRESSED){
					lc->upcomingReceipted();
					state = ERR_STATE_ERROR_RECEIPTED;
				}
			}
			break;
		case ERR_STATE_ERROR_RECEIPTED:
			if(pulseCode == PULSE_FROM_ISRHANDLER){
				if(pulseVal == BTN_START_PRESSED){
					lc->operatingNormal();
					//msg puck error solved, reihenfolge unstop und msg puck?!
					sendPuckReply();
					aHal->engineFullUnstop();
					state = ERR_STATE_IDLE;
				}
			}
			break;
		case ERR_STATE_TURNOVER_BAND2:
			if(pulseCode == PULSE_FROM_ISRHANDLER){
				if(pulseVal == BTN_RESET_PRESSED){
					lc->upcomingReceipted();
					state = ERR_STATE_TURNOVER_BAND2_RECEIPTED;
				}
			}
			break;
		case ERR_STATE_TURNOVER_BAND2_RECEIPTED:
			if(pulseCode == PULSE_FROM_ISRHANDLER){
				if(pulseVal == SB_START_OPEN){
					isSbStartOpen = true;
				} else if(pulseVal == BTN_START_PRESSED && isSbStartOpen){
					isSbStartOpen = false;
					lc->operatingNormal();
					//msg puck error solved, reihenfolge unstop und msg puck?!
					sendPuckReply();
					aHal->engineFullUnstop();
					state = ERR_STATE_IDLE;
				}
			}
			break;
		default:
			printf("nop\n");
		}
	}
}

void ErrorFSM::stop() {
	HAWThread::stop();

	if (ConnectDetach(replyCoid) == -1) {
		printf("ErrorFSM: Error in ConnectDetach\n");
	}

	if (ChannelDestroy(replyChid) == -1) {
		printf("ErrorFSM: Error in ChannelDestroy\n");
	}

	if (ChannelDestroy(ownChid) == -1) {
		printf("ErrorFSM: Error in ChannelDestroy\n");
	}
}

void ErrorFSM::shutdown() {
}

int ErrorFSM::getErrorFSMChid() {
	return ownChid;
}


int ErrorFSM::getReplyChid() {
	return replyChid;
}

void ErrorFSM::sendPuckReply(){
	int rc = MsgSendPulse(replyCoid, SIGEV_PULSE_PRIO_INHERIT, PULSE_FROM_ERR_FSM, 0/*ERROR_SOLVED*/);
	if (rc < 0) {
		printf("ErrorFSM: Error in MsgSendPulse\n");
	}
}
