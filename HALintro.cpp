/*
 * HALintro.cpp
 *
 *  Created on: 18.10.2012
 *      Author: aay973
 */

#include "HALintro.h"
#include "HWaccess.h"
//#include "Addresses.h"

#include <stdint.h>

HALintro* HALintro::instance = NULL;

HALintro::HALintro() {
	// Initialisierung der Digitalen IO Karte
	//out8(DIO_BASE + DIO_CONTROL_BLA, 0x8A);
	out8(0x300 + 0x03, 0x8A);

	//-->nicht nötig aber sicherer
	//out8(DIO_BASE + DIO_OFFS_A, 0x00);
	//out8(DIO_BASE + DIO_OFFS_C, 0x00);
}

HALintro::~HALintro() {
	delete instance;
	instance = NULL;
}

HALintro* HALintro::getInstance() {

	// Zugriffsrechte fuer den Zugriff auf die HW holen
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		perror("ThreadCtl access failed\n");
		return NULL;
	}

	if (instance == NULL) {
		instance = new HALintro();
	}

	return instance;
}

void HALintro::lampeRotAn() {
	uint8_t val = in8(0x300 + 0x00);
	out8(0x300 + 0x00, val | 0x80);
}

void HALintro::lampeRotAus() {
	uint8_t val = in8(0x300 + 0x00);
	out8(0x300 + 0x00, val & ~(0x80));
}
