/**
 * SE2 WiSe 2012
 * HAL (hardware abstraction layer)
 *
 * Some bla bla bla for this file
 * 
 * @file HALintro.cpp
 * @author Chris Addo
 *         Jens Eberwein
 *         Tristan Rudat
 *         Martin Slowikowski
 * @date 2012-10-18
 * @version 0.1
 * 
 */

#include "HAL.h"

HAL* HAL::instance = NULL;
Mutex* HAL::halMutex = new Mutex();
Mutex* HAL::halInstanceMutex = new Mutex();

HAL::HAL()
{
#ifdef SIMULATION
	std::cout << "Simulation aktiv" << std::endl;
	std::cout << "Zum Aufbau der Verbindung muss Die Festo Simulation schon laufen." << std::endl;
	IOaccess_open(); // Baue die Verbindung zur Simulation auf
#endif
	// Initialisierung der Digitalen IO Karte
	//out8(DIO_BASE + DIO_CONTROL_BLA, 0x8A);
	out8(PORT_CTRL, 0x82);

	//-->nicht nötig aber sicherer
	out8(PORT_A, 0x00);
	out8(PORT_C, 0x00);
}

HAL::~HAL()
{
	delete instance;
	instance = NULL;
	halMutex->~Mutex();
	halInstanceMutex->~Mutex();
}

HAL* HAL::getInstance()
{

	// Zugriffsrechte fuer den Zugriff auf die HW holen
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0))
	{
		perror("ThreadCtl access failed\n");
		return NULL;
	}

	halInstanceMutex->lock();

	if (instance == NULL)
	{
		instance = new HAL();
	}

	halInstanceMutex->unlock();

	return instance;
}

void HAL::lightRed(bool isOn)
{
	uint8_t val = in8(PORT_A);
	
	halMutex->lock();

	if(isOn)
	{
		out8(PORT_A, val | LIGHT_RED);
	} 
	else 
	{
		out8(PORT_A, val & ~(LIGHT_RED));
	}

	halMutex->unlock();
}

void HAL::lightYellow(bool isOn)
{
	uint8_t val = in8(PORT_A);

	halMutex->lock();

    if(isOn)
	{
		out8(PORT_A, val | LIGHT_YELLOW);
	}
	else
	{
		out8(PORT_A, val & ~(LIGHT_YELLOW));
	}

    halMutex->unlock();
}

void HAL::lightGreen(bool isOn)
{
	uint8_t val = in8(PORT_A);

    halMutex->lock();

    if(isOn)
	{
		out8(PORT_A, val | LIGHT_GREEN);
	}
	else
	{
		out8(PORT_A, val & ~(LIGHT_GREEN));
	}

    halMutex->unlock();
}

void HAL::engineRight(bool isSlow)
{
	uint8_t val = in8(PORT_A);

    halMutex->lock();

    if(isSlow)
	{
		out8(PORT_A, val | ENGINE_SLOW_RIGHT);
	}
	else
	{
		out8(PORT_A, (val | ENGINE_RIGHT) & ~(ENGINE_SLOW));
		//out8(PORT_A, val & ~(ENGINE_SLOW_RIGHT));
	}

    halMutex->unlock();
}

void HAL::engineLeft(bool isSlow)
{
	uint8_t val = in8(PORT_A);

	halMutex->lock();

    if(isSlow)
	{
		out8(PORT_A, val | ENGINE_SLOW_LEFT);
	}
	else
	{
		out8(PORT_A, (val | ENGINE_LEFT) & ~(ENGINE_SLOW));
		//out8(PORT_A, val & ~(ENGINE_SLOW_LEFT));
	}

    halMutex->unlock();
}

void HAL::engineStop()
{
	uint8_t val = in8(PORT_A);

    halMutex->lock();
	out8(PORT_A, val | ENGINE_STOP);
    halMutex->unlock();
}

void HAL::engineUnstop()
{
	uint8_t val = in8(PORT_A);

    halMutex->lock();
	out8(PORT_A, val & ~(ENGINE_STOP));
    halMutex->unlock();
}

void HAL::gate(bool isOpen)
{
	uint8_t val = in8(PORT_A);

    halMutex->lock();

    if(isOpen)
	{
		out8(PORT_A, val | GATE);
	}
	else
	{
		out8(PORT_A, val & ~(GATE));
	}

    halMutex->unlock();
}

void HAL::ledStart(bool isOn)
{
	uint8_t val = in8(PORT_C);

    halMutex->lock();

    if(isOn)
	{
		out8(PORT_C, val | LED_START);
	}
	else
	{
		out8(PORT_C, val & ~(LED_START));
	}

    halMutex->unlock();
}

void HAL::ledReset(bool isOn)
{
	uint8_t val = in8(PORT_C);

    halMutex->lock();

    if(isOn)
	{
		out8(PORT_C, val | LED_RESET);
	}
	else
	{
		out8(PORT_C, val & ~(LED_RESET));
	}

    halMutex->unlock();
}

void HAL::ledQ1(bool isOn)
{
	uint8_t val = in8(PORT_C);

    halMutex->lock();

    if(isOn)
	{
		out8(PORT_C, val | LED_Q1);
	}
	else
	{
		out8(PORT_C, val & ~(LED_Q1));
	}

    halMutex->unlock();
}

void HAL::ledQ2(bool isOn)
{
	uint8_t val = in8(PORT_C);

	halMutex->lock();

    if(isOn)
	{
		out8(PORT_C, val | LED_Q2);
	}
	else
	{
		out8(PORT_C, val & ~(LED_Q2));
	}

    halMutex->unlock();
}
