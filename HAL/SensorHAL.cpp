/**
 * SE2 WiSe 2012
 * Sensor HAL class for ISR and sensor management
 *
 * Offers functions for the different sensor the festo
 * system has, like light barriers, metal and height sensor,
 * buttons. All nterrupt driven, except the height control.
 * ISR tells kernel to send a pulse msg to a specific channel.
 *
 * \file SensorHAL.cpp
 * \author Chris Addo
 *         Jens Eberwein
 *         Tristan Rudat
 *         Martin Slowikowski
 * \date 2012-11-02
 * \version 0.2
 *
 */

#include "SensorHAL.h"

SensorHAL* SensorHAL::instance = NULL;
Mutex* SensorHAL::sensorInstanceMutex = new Mutex();

SensorHAL::SensorHAL() {
	initInterrupt();
}

SensorHAL::~SensorHAL() {
	if (instance != NULL) {
		delete instance;
		instance = NULL;
		sensorInstanceMutex->~Mutex();
	}
}

SensorHAL* SensorHAL::getInstance() {
	if (!instance) {
		sensorInstanceMutex->lock();
		if (!instance) {
			instance = new SensorHAL;
#ifdef DEBUG_SENSORHAL
			printf("Debug SensorHAL: New SensorHAL instance created\n");
#endif
		}
		sensorInstanceMutex->unlock();
	}

	return instance;
}

const struct sigevent* ISR(void *arg, int id) {
	struct sigevent *event = (struct sigevent *) arg;

	int portB = 0;
	int portC = 0;

	int iir = in8(DIO_INTERRUPT_READ_CLEAR); //Status auslesen und IRQ zur�ck setzen

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

//TODO singleton, mutex f�r in/out, da nur einmal beim Setup ...
//eigentlich glob mutex needed, angenommen thread fuer Actor und Sensor HAL
//initen sich zeitgleich ... unwahrscheinlich, aber moeglich
void SensorHAL::initInterrupt() {
	//Create channel for pulse notification
	if ((chid = ChannelCreate(0)) == -1) {
		printf("SensorHAL: Error in ChannelCreate\n");
	}

	//Connect to channel
	if ((coid = ConnectAttach(0, 0, chid, _NTO_SIDE_CHANNEL, 0)) == -1) {
		printf("SensorHAL: Error in ConnectAttach\n");
	}

	//Initialisiere ein sigevent als Pulse
	SIGEV_PULSE_INIT(&event, coid, SIGEV_PULSE_PRIO_INHERIT, PULSE_FROM_ISR, 0);

	//Get rights
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		printf("ThreadCtl access failed\n");
		exit(EXIT_FAILURE);
	}

	//Init Port A, B, C, if HAl doesnt already
	out8(PORT_CTRL, DIO_INIT);

	//Enable IRQs for PortB and PortC
	out8(DIO_INTERRUPT_ENABLE_REG, DIO_INTERRUPT_ENABLE_BC);

	//Reset IRQs
	out8(DIO_INTERRUPT_CLEAR_REG, 0x00);

	//Registriere die Interrupt Service Routine
	if ((interruptId = InterruptAttach(DIO_IRQ, ISR, &event, sizeof(event), 0))
			== -1) {
		printf("SensorHAL: Error in InterruptAttach\n");
	}
}

int SensorHAL::getHeight() {
	/*
	 Bohrung oben	3506,3524,3528
	 Bohrung unten	2470,2478,2480
	 zu flach	2731,2737
	 Bohrung oben oM	3492
	 */
	int hoehe = -1;
	int i;

	out8(AIO_PORT_A, AIO_GET_VAL);

	for (i = 0; i < 50; i++) {
		//Bit 7 goes HIGH when an A/D conversion completes
		if ((in8(AIO_BASE) & (1 << 7))) { // == (1<<7)
			hoehe = in16(AIO_PORT_A);
			break;
		}
	}
	return hoehe;
}

int SensorHAL::getChid() {
	return chid;
}

int SensorHAL::getCoid() {
	return coid;
}

void SensorHAL::stopInterrupt() {
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		printf("ThreadCtl access failed\n");
		exit(EXIT_FAILURE);
	}

	if (InterruptDetach(interruptId) == -1) {
		printf("SensorHAL: Error InterruptDetach\n");
	}

	if (ConnectDetach(coid) == -1) {
		printf("SensorHAL: Error in ConnectDetach\n");
	}

	if (ChannelDestroy(chid) == -1) {
		printf("SensorHAL: Error in ChannelDestroy\n");
	}
}

