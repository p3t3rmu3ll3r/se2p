/*
 * Light.h
 *
 *  Created on: 16.10.2012
 *      Author: aay973
 */

#ifndef LIGHT_H_
#define LIGHT_H_

class Light {
public:
	Light();
	virtual ~Light();

	void lightGreen();
	void lightYellow();
	void lightRed();
	void blink();

};

#endif /* LIGHT_H_ */
