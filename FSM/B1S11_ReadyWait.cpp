/*
 * B1S11_ReadyWait.cpp
 *
 *  Created on: 01.12.2012
 *      Author: martin
 */

#include "B1S11_ReadyWait.h"

B1S11_ReadyWait::B1S11_ReadyWait(Controller* controller) {
	this->controller = controller;

#ifdef DEBUG_STATE_PRINTF
	printf("DEBUG STATE: Puck%d -> B1S11_ReadyWait \n", this->controller->getID());
#endif
	actorHAL->engineFullStop();
	rs232_1->sendMsg(RS232_BAND1_WAITING);
	//TODO timermagic, if no ack returns
}

B1S11_ReadyWait::~B1S11_ReadyWait() {
}

void B1S11_ReadyWait::rs232Band2Ack(){
	//TODO timermagic, if lust... else wait 4evr
}

void B1S11_ReadyWait::rs232Band2Ready(){
	controller->puckType = PUCK_HANDOVER;
	actorHAL->engineFullUnstop();
	new (this) B1S08_End(controller);
}
