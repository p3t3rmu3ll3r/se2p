/*
 * HALintro.h
 *
 *  Created on: 18.10.2012
 *      Author: aay973
 */

#ifndef HALINTRO_H_
#define HALINTRO_H_

class HALintro {
private:
	static HALintro* instance;

	HALintro();
public:
	~HALintro();

	static HALintro* getInstance();

	void lampeRotAn();
	void lampeRotAus();
};

#endif /* HALINTRO_H_ */
