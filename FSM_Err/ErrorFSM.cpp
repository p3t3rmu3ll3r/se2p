/*
 * ErrorFSM.cpp
 *
 *  Created on: 26.11.2012
 *      Author: martin
 */

#include "ErrorFSM.h"

ErrorFSM::ErrorFSM() {
	state = ERR_STATE_IDLE;
	aHal = ActorHAL::getInstance();
	lc = LightController::getInstance();
	ph = PuckHandler::getInstance();

	//Create channel for pulse notification
	if ((ownChid = ChannelCreate(0)) == -1) {
		printf("ErrorFSM: Error in ChannelCreate\n");
	}

	if ((replyCoid = ConnectAttach(0, 0, ph->getReplyChid(), _NTO_SIDE_CHANNEL, 0)) == -1) {
		printf("ErrorFSM: Error in ConnectAttach\n");
	}
}

ErrorFSM::~ErrorFSM() {
}

void ErrorFSM::execute(void*) {
	int rc;
	struct _pulse pulse;
	int pulseVal;
	int pulseCode;

	lc->operatingNormal();

	while (!isStopped()) {
		rc = MsgReceivePulse(ownChid, &pulse, sizeof(pulse), NULL);
		if (rc < 0) {
			printf("ErrorFSM: Error in recv pulse\n");
			if (isStopped()) {
				break;
			}
		}
		pulseCode = pulse.code;
		pulseVal = pulse.value.sival_int;

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

	if (ChannelDestroy(ownChid) == -1) {
		printf("ErrorFSM: Error in ChannelDestroy\n");
	}
}

void ErrorFSM::shutdown() {
}

int ErrorFSM::getErrorFSMChid() {
	return ownChid;
}

void ErrorFSM::sendPuckReply(){
	int rc = MsgSendPulse(replyCoid, SIGEV_PULSE_PRIO_INHERIT, PULSE_FROM_ERR_FSM, 0/*ERROR_SOLVED*/);
	if (rc < 0) {
		printf("ErrorFSM: Error in MsgSendPulse\n");
	}
}
