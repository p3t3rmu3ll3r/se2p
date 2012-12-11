/**
 * SE2 WiSe 2012
 *
 * Contains all messages that ISRHandler can send as a
 * pulse message to the Dispatcher.
 * The macro MESSAGE_SIZE defines count of signals.
 *
 * @file time_values.h
 * @author Chris Addo
 *         Jens Eberwein
 *         Tristan Rudat
 *         Martin Slowikowski
 * @date 2012-12-06
 * @version 0.1
 *
 */

#ifndef TIME_VALUES_H_
#define TIME_VALUES_H_


//TODO: check dem 8!7C|-|35
#define TIME_VALUE_CLOSE_GATE_SEC 1
#define TIME_VALUE_CLOSE_GATE_MSEC 400

//TODO: check dem 8!7C|-|35
#define TIME_VALUE_SLIDE_FULL_SEC 1
#define TIME_VALUE_SLIDE_FULL_MSEC 0

//TODO: check dem 8!7C|-|35
#define TIME_VALUE_SEG1_MIN_SEC 1
#define TIME_VALUE_SEG1_MIN_MSEC 700
#define TIME_VALUE_SEG1_MAX_SEC 2
#define TIME_VALUE_SEG1_MAX_MSEC 500

#define TIME_VALUE_SEG2_MIN_SEC 2500
#define TIME_VALUE_SEG2_MAX_SEC 4500

#define TIME_VALUE_SEG3_MIN_SEC 3000
#define TIME_VALUE_SEG3_MAX_SEC 5000

#endif /* TIME_VALUES_H_ */
