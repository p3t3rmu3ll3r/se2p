/*
 * PuckHandler.h
 *
 *  Created on: 24.11.2012
 *      Author: martin
 */

#ifndef PUCKHANDLER_H_
#define PUCKHANDLER_H_

#include <queue>
#include <iostream.h>
#include "Controller.h"
#include "Mutex.h"

#define MAX_PUCKS_BAND1 12

class PuckHandler {
public:

	static PuckHandler* getInstance();

	void addPuckToBand1(Controller* contr);
	void addPuckToSeg1(Controller* contr);
	void addPuckToSeg2(Controller* contr);
	void addPuckToSeg3(Controller* contr);

	void removePuckFromBand1();
	void removePuckFromSeg1();
	void removePuckFromSeg2();
	void removePuckFromSeg3();

	bool isBand1Empty();
	bool checkIfFirstElemInSeg1(Controller* contr);
	bool checkIfFirstElemInSeg2(Controller* contr);
	bool checkIfFirstElemInSeg3(Controller* contr);

	virtual ~PuckHandler();

private:

	PuckHandler();

	static PuckHandler* instance;
	static Mutex* puckHandlerInstanceMutex;

	queue<Controller*> elemsOnBand1;
	queue<Controller*> elemsInSeg1;
	queue<Controller*> elemsInSeg2;
	queue<Controller*> elemsInSeg3;
};

#endif /* PUCKHANDLER_H_ */
