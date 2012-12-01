/**
 * SE2 WiSe 2012
 *
 * Contains all messages that ISRHandler can send as a
 * pulse message to the Dispatcher.
 * The macro MESSAGE_SIZE defines count of signals.
 *
 * @file messages.h
 * @author Chris Addo
 *         Jens Eberwein
 *         Tristan Rudat
 *         Martin Slowikowski
 * @date 2012-11-28
 * @version 0.6
 *
 */

#ifndef MESSAGES_H_
#define MESSAGES_H_

#define SENSOR_MESSAGES_SIZE 19
#define RS232_MESSAGES_SIZE 3

//all this messages need to be dispatched
enum sensorMessages {
	SB_START_OPEN,
	SB_START_CLOSED,
	SB_HEIGHTCONTROL_OPEN,
	SB_HEIGHTCONTROL_CLOSED,
	SB_GATE_OPEN,
	SB_GATE_CLOSED,
	MS_METAL_TRUE,
	SB_SLIDE_OPEN,
	SB_SLIDE_CLOSED,
	SB_END_OPEN,
	SB_END_CLOSED,
	BTN_START_PRESSED,
	BTN_START_RELEASED,
	BTN_STOP_PRESSED,
	BTN_STOP_RELEASED,
	BTN_RESET_PRESSED,
	BTN_RESET_RELEASED,
	BTN_ESTOP_PRESSED,
	BTN_ESTOP_RELEASED,
};

enum rs232Messages {
	RS232_BAND2_ACK,
	RS232_BAND2_READY,
	RS232_BAND1_WAITING,
};

#endif /* MESSAGES_H_ */
