/*
 * B2S02_Seg1.cpp
 *
 *  Created on: 24.11.2012
 *      Author: martin
 */

#include "B2S02_Seg1.h"

B2S02_Seg1::B2S02_Seg1(Controller* controller) {
	this->controller = controller;

	printf("DEBUG STATE: Puck%d -> B2S02_Seg1 \n", this->controller->getID());
}

B2S02_Seg1::~B2S02_Seg1() {
	rs232_1->sendMsg(RS232_PUCK_ARRIVED_ON_BAND2);
}

void B2S02_Seg1::sbHeightcontrolOpen() {
	new (this) B2S03_Height(controller);
}
