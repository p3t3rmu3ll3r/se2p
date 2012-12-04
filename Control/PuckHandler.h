/**
 * SE2 WiSe 2012
 * PuckHandler
 *
 * PuckHandler handles pucks placed on Band1 or Band2.
 * There are queues for each segment on the band conveyor and for the whole
 * band conveyor, containing pucks placed on the band conveyor.
 *
 * @file PuckHandler.h
 * @author Chris Addo
 *         Jens Eberwein
 *         Tristan Rudat
 *         Martin Slowikowski
 * @date 2012-11-28
 * @version 0.6
 *
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
	#define MAX_PUCKS_BAND 12
#else
	#define MAX_PUCKS_BAND 1
#endif

#define DEBUG_PuckHandler

class PuckHandler {
public:
	/**
	 * Class implemented as singleton. Method returns an instance of the
	 * PuckHandler to work with
	 *
	 * @return PuckHandler instance
	 */
	static PuckHandler* getInstance();

	/**
	 * Adds a puck to the band conveyor vector, contains all pucks actually
	 * placed on the conveyor.
	 *
	 * @param controller (Puck)
	 */
	void addPuckToBand(Controller* contr);

	/**
	 * Adds a puck to the band conveyor segment1 queue, contains all pucks actually
	 * placed between entry and height control.
	 *
	 * @param controller (Puck)
	 */
	void addPuckToSeg1(Controller* contr);

	/**
	 * Adds a puck to the band conveyor segment2 queue, contains all pucks actually
	 * placed between height control and gate.
	 *
	 * @param controller (Puck)
	 */
	void addPuckToSeg2(Controller* contr);

	/**
	 * Adds a puck to the band conveyor segment3 queue, contains all pucks actually
	 * placed between gate and end.
	 *
	 * @param controller (Puck)
	 */
	void addPuckToSeg3(Controller* contr);

	/**
	 * Removes a puck from the band conveyor vector
	 *
	 * @param controller (Puck)
	 */
	void removePuckFromBand(Controller* contr);

	/**
	 * Removes first (pop) puck from the band conveyor segment1 queue
	 */
	void removePuckFromSeg1();

	/**
	 * Removes first (pop) puck from the band conveyor segment2 queue
	 */
	void removePuckFromSeg2();

	/**
	 * Removes first (pop) puck from the band conveyor segment3 queue
	 */
	void removePuckFromSeg3();

	/**
	 * Returns if band conveyor is empty or not
	 *
	 * @return [true if empty, false if not]
	 */
	bool isBandEmpty();

	/**
	 * Returns if only one puck is on band conveyor
	 *
	 * @return [true if yes, false if not]
	 */
	bool isOnlyOneElemeOnBand();

	/**
	 * Returns if given controller (puck) is first in segment1 queue
	 *
	 * @return [true if yes, false if not]
	 */
	bool checkIfFirstElemInSeg1(Controller* contr);

	/**
	 * Returns if given controller (puck) is first in segment2 queue
	 *
	 * @return [true if yes, false if not]
	 */
	bool checkIfFirstElemInSeg2(Controller* contr);

	/**
	 * Returns if given controller (puck) is first in segment3 queue
	 *
	 * @return [true if yes, false if not]
	 */
	bool checkIfFirstElemInSeg3(Controller* contr);

	/**
	 * Initializes all controllers (Pucks, 12 per define at the moment). Each puck
	 * is registered for all signals at the Dispatcher.
	 */
	void initializePucks();

	/**
	 * If a new controller (Puck) is placed on band conveyor, on of MAX_PUCKS_BAND
	 * active flag is set.
	 */
	void activatePuck();

	/**
	 * standard destructor, destroys instance and corresponding mutex.
	 */
	virtual ~PuckHandler();

	/**
	 * Resets the PuckHandler, including mutexes, queues, vectors, variables
	 * for a new clean run.
	 */
	void reset();


	/**
	 * Helper method: prints status of all used queues
	 */
	void printQueueStatus();

	int getDispChid();

private:

	/**
	 * Standard constructor: singleton. Initializes all used mutexes
	 */
	PuckHandler();

	/**
	 * resets all the pucks
	 */
	void resetAllPucks();

	/**
	 * Instance for the PuckHandler
	 */
	static PuckHandler* instance;

	/**
	 * Mutex for securing singleton pattern
	 */
	static Mutex* puckHandlerInstanceMutex;

	/**
	 * Mutex for securing access to segment1 queue
	 */
	Mutex* seg1Mutex;

	/**
	 * Mutex for securing access to segment2 queue
	 */
	Mutex* seg2Mutex;

	/**
	 * Mutex for securing access to segment3 queue
	 */
	Mutex* seg3Mutex;

	/**
	 * Mutex for securing access to puck vector
	 */
	Mutex* pucksBandMutex;

	/**
	 * Contains all MAX_PUCKS_BAND after initializePucks() was called
	 */
	vector<Controller*> pucks;

	/**
	 * Contains all pucks that are currently on band conveyor
	 */
	vector<Controller*> pucksOnBand;

	/**
	 * Contains all pucks that are currently in segment1
	 */
	queue<Controller*> pucksInSeg1;

	/**
	 * Contains all pucks that are currently in segment2
	 */
	queue<Controller*> pucksInSeg2;

	/**
	 * Contains all pucks that are currently in segment3
	 */
	queue<Controller*> pucksInSeg3;

	/**
	 * Instance of the Dispatcher to work with
	 */
	Dispatcher* disp;

	/**
	 * Instance of the Dispatcher to work with
	 */
	int dispChid;

};

#endif /* PUCKHANDLER_H_ */
