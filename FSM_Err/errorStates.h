/*
 * errorStaters.h
 *
 *  Created on: 26.11.2012
 *      Author: martin
 */

#ifndef ERRORSTATES_H_
#define ERRORSTATES_H_

enum state {
	ERR_STATE_IDLE,
	ERR_STATE_SLIDE_FULL,
	ERR_STATE_SLIDE_FULL_RECEIPTED,
	ERR_STATE_TURNOVER,
	ERR_STATE_ERROR,
	ERR_STATE_ERROR_RECEIPTED,
};

#endif /* ERRORSTATES_H_ */
