/*
 * Light.cpp
 *
 *  Created on: 16.10.2012
 *      Author: Tristan Rudat & Chris Addo
 *
 *  Bitmuster Beispiel zur Verschiebung auf Adressen
 *
 *  0010 0100
 * 	1101 1111
 *  0000 0100

0x24
0xDF
0x04

 *
 */

#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include "Light.h"
#include "HWaccess.h"

using namespace std;


#define D_IOBASE 0x300 								// Anfangsadresse Ports
#define DIGITAL_CARD_CONTROL (D_IOBASE + 0x03) 		// Adresse von Card Control
#define DIGITAL_CARD_CROUP0_PORTA (D_IOBASE + 0x00) // Adresse von Port A

Light::Light() {
	#ifdef SIMULATION
		cout << "Simulation aktiv" << endl;
		cout << "Zum Aufbau der Verbindung muss Die Festo Simulation schon laufen." << endl;
		IOaccess_open(); // Baue die Verbindung zur Simulation auf
	#endif

	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		perror("ThreadCtl access failed\n");
//		return -1;
	}

}
Light::~Light() {
	#ifdef SIMULATION
		IOaccess_close(); // Schließe die Verbindung zur Simulation
	#endif
}

void Light::lightGreen() {
	cout << "Leuchte Grün" << endl;
		out8(D_IOBASE, 0x20);
	sleep(1);
}

void Light::lightYellow() {
	cout << "Leuchte gelb!" << endl;
		out8(D_IOBASE, 0x40);
	sleep(1);
}

void Light::lightRed() {
	cout << "Leuchte rot!" << endl;
		out8(D_IOBASE, 0x80);
	sleep(1);
}

void Light::blink() {
		out8(D_IOBASE, 0xC0);
		sleep(3);
		out8 (D_IOBASE, !0xC0);
		sleep(3);
		out8 (D_IOBASE, 0xC0);
		sleep(3);
		out8 (D_IOBASE, !0xC0);
	sleep(1);
}
