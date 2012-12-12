/*
 * B1S08_End.cpp
 *
 *  Created on: 25.11.2012
 *      Author: martin
 */

#include "B1S08_End.h"

B1S08_End::B1S08_End(Controller* controller) {
	this->controller = controller;

#ifdef DEBUG_STATE_PRINTF
	printf("DEBUG STATE: Puck%d -> B1S08_End \n", this->controller->getID());
#endif

	if(this->controller->puckType == PUCK_TURNOVER){
		new (this) B1S09_ERR_TurnOver(this->controller);
	} else if(this->controller->puckType == PUCK_ACCEPTED){
		new (this) B1S11_ReadyWait(this->controller);
	}
}

B1S08_End::~B1S08_End() {
}

void B1S08_End::rs232PuckArrivedOnBand2(){
	puckHandler->removePuckFromBand(controller);
	if(puckHandler->isBandEmpty()){
		actorHAL->engineStop();
	}
	controller->resetController();
}

void B1S08_End::sbEndClosed(){
	puckHandler->resetAllSenseorFuncCounters();
	/*
	//some moar seconds engineRight();
	//TODO timer magic, in sbEndClosed nur timer starten
	//TODO bei neuer methode popped sich der puck dann und haelt ggf an
	//pop at first or last?!
	//test with sleep, but carefully :>
	puckHandler->removePuckFromBand(controller);
	if(puckHandler->isBandEmpty()){
		sleep(3); //TODO: dont 4get da sl33p
		actorHAL->engineStop();
	}
	controller->resetController();*/
}

