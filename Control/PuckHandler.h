/*
 * PuckHandler.h
 *
 *  Created on: 24.11.2012
 *      Author: martin
 */

#ifndef PUCKHANDLER_H_
#define PUCKHANDLER_H_

#include <queue>
#include <vector>
#include <iostream.h>
#include "Controller.h"
#include "Dispatcher.h"
#include "Mutex.h"
#include "bandselection.h"


#ifdef BAND_1
	#define MAX_PUCKS_BAND1 12
#else
	#define MAX_PUCKS_BAND1 1
#endif

#define DEBUG_PuckHandler

class PuckHandler {
public:

	static PuckHandler* getInstance();

	void addPuckToBand(Controller* contr);
	void addPuckToSeg1(Controller* contr);
	void addPuckToSeg2(Controller* contr);
	void addPuckToSeg3(Controller* contr);

	void removePuckFromBand(Controller* contr);
	void removePuckFromSeg1();
	void removePuckFromSeg2();
	void removePuckFromSeg3();

	bool isBand1Empty();
	bool isOnlyOneElemeOnBand1();
	bool checkIfFirstElemInSeg1(Controller* contr);
	bool checkIfFirstElemInSeg2(Controller* contr);
	bool checkIfFirstElemInSeg3(Controller* contr);

	void initializePucks(Dispatcher* disp);
	void activatePuck();

	virtual ~PuckHandler();
	void getQueues();

private:

	PuckHandler();

	static PuckHandler* instance;
	static Mutex* puckHandlerInstanceMutex;

	Mutex* seg1Mutex;
	Mutex* seg2Mutex;
	Mutex* seg3Mutex;
	Mutex* pucksBandMutex;

	vector<Controller*> pucks;
	vector<Controller*> pucksOnBand1;

	queue<Controller*> pucksInSeg1;
	queue<Controller*> pucksInSeg2;
	queue<Controller*> pucksInSeg3;

};

#endif /* PUCKHANDLER_H_ */
