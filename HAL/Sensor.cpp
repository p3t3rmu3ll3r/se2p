/*
 * Sensor.cpp
 *
 *  Created on: 28.10.2012
 *      Author: martin
 */

#include "Sensor.h"
#include <stdint.h>
#include <iostream>
#include <unistd.h>

Sensor::Sensor() {
	initInterrupt();
}

Sensor::~Sensor() {
	// TODO Auto-generated destructor stub
}

const struct sigevent* ISR(void *arg, int id) {
	struct sigevent *event = (struct sigevent *) arg;

	int portB = 0;
	int portC = 0;


	int iir = in8(DIO_INTERRUPT_READ_CLEAR); //Status auslesen und IRQ zurück setzen

	event->sigev_value.sival_int = 0;
	event->sigev_notify = SIGEV_PULSE;

	if (iir == PORTB_INTERRUPT || iir == PORTC_INTERRUPT) {
		portB = in8(PORT_B);
		portC = in8(PORT_C) & 0xF0;
		portC = portC << 4;
		event->sigev_value.sival_int = portC | portB;
	} else {
		return NULL;
	}

	out8(DIO_INTERRUPT_CLEAR_REG, 0x00);

	return event;
}


//TODO singleton, mutex für in/out
void Sensor::initInterrupt() {
	//Create channel for pulse notification
	if((chid = ChannelCreate(0)) == -1){
		printf("Error in ChannelCreate\n");
	}

	//Connect to channel
	if((coid = ConnectAttach(0, 0, chid, _NTO_SIDE_CHANNEL, 0)) == -1) {
		printf("Error in ConnectAttach\n");
	}

	//Initialisiere ein sigevent als Pulse
	SIGEV_PULSE_INIT( &event, coid, SIGEV_PULSE_PRIO_INHERIT,5 , 0 );

	//Get rights
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		printf("ThreadCtl access failed\n");
		exit(EXIT_FAILURE);
	}

	//Init Port A, B, C, if HAl doesnt already
	out8(PORT_CTRL, 0x8A);

	//Enable IRQs for PortB and PortC
    out8(DIO_INTERRUPT_ENABLE_REG, DIO_INTERRUPT_ENABLE_BC);

    //Reset IRQs
    out8(DIO_INTERRUPT_CLEAR_REG, 0x00);


	//Registriere die Interrupt Service Routine
	if((interruptId = InterruptAttach(11, ISR, &event, sizeof(event), 0)) == -1){
		printf("Error in InterruptAttach\n");
	}
}

int Sensor::getHeight() {
	/*
		Bohrung oben	3506,3524,3528
		Bohrung unten	2470,2478,2480
		zu flach	2731,2737
		Bohrung oben oM	3492
	*/
	int hoehe = -1;
	int i;

	out8(AIO_PORT_A, AIO_GET_VAL);

	for (i = 0; i < 10000; i++) {
		//Bit 7 goes HIGH when an A/D conversion completes
		if ((in8(AIO_BASE) & (1 << 7))) { // == (1<<7)
			hoehe = in16(AIO_PORT_A);
			break;
		}
	}
	return hoehe;
}

int Sensor::getChid(){
	return chid;
}

int Sensor::getCoid(){
	return coid;
}

