/**
 * SE2 WiSe 2012
 * I/O addresses
 *
 * Some bla bla bla for this file
 * 
 * @file address.h
 * @author Chris Addo
 *         Jens Eberwein
 *         Tristan Rudat
 *         Martin Slowikowski
 * @date 2012-10-18
 * @version 0.1
 * 
 */

#ifndef ADDRESS_H_
#define ADDRESS_H_

// General defines

#define DIO_BASE		0x300	// Base Adresse
#define DIO_OFFS_A		0x00	// Port A Offset
#define DIO_OFFS_B		0x01	// Port B Offset
#define DIO_OFFS_C		0x02	// Port C Offset
#define DIO_OFFS_CTRL	0x03	// Control Register Offset

#define PORT_A		(DIO_BASE + DIO_OFFS_A)	
#define PORT_B		(DIO_BASE + DIO_OFFS_B)
#define PORT_C		(DIO_BASE + DIO_OFFS_C)
#define PORT_CTRL	(DIO_BASE + DIO_OFFS_CTRL)

// Individual bits
#define BIT0	0x01
#define BIT1	0x02
#define BIT2	0x04
#define BIT3	0x08
#define BIT4	0x10
#define BIT5	0x20
#define BIT6	0x40
#define BIT7	0x80

// Port A
#define ENGINE_RIGHT	0x01
#define ENGINE_LEFT		0x02
#define ENGINE_SLOW		0x04
#define ENGINE_STOP		0x08
#define GATE			0x10
#define LIGHT_GREEN		0x20
#define LIGHT_YELLOW	0x40
#define LIGHT_RED		0x80

#define ENGINE_SLOW_LEFT	(ENGINE_SLOW + ENGINE_LEFT)
#define ENGINE_SLOW_RIGHT	(ENGINE_SLOW + ENGINE_RIGHT)

// Port C
#define LED_START	0x01
#define LED_RESET	0x02
#define LED_Q1		0x04
#define LED_Q2		0x08


#endif /* ADDRESS_H_ */
