/**
 * SE2 WiSe 2012
 * HAL (hardware abstraction layer)
 *
 * Some bla bla bla for this file
 * 
 * @file HALintro.h
 * @author Chris Addo
 *         Jens Eberwein
 *         Tristan Rudat
 *         Martin Slowikowski
 * @date 2012-10-18
 * @version 0.1
 * 
 */

#ifndef HALINTRO_H_
#define HALINTRO_H_

#include <stdint.h>
#include <iostream>
#include <unistd.h>

#include "address.h"
#include "HWaccess.h"
#include "Mutex/Mutex.h"

class HAL {
private:
	static HAL* instance;
	static Mutex* halInstanceMutex;
	static Mutex* halMutex;

	HAL();
public:
	~HAL();

	static HAL* getInstance();

	// Port A
	void engineRight(bool isSlow);
	void engineLeft(bool isSlow);
	void engineStop();
	void engineUnstop();
	void gate(bool isOpen);
	void lightRed(bool isOn);
	void lightYellow(bool isOn);
	void lightGreen(bool isOn);

	// Port C
	void ledStart(bool isOn);
	void ledReset(bool isOn);
	void ledQ1(bool isOn);
	void ledQ2(bool isOn);
};

#endif /* HALINTRO_H_ */
