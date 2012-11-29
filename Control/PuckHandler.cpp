/**
 * SE2 WiSe 2012
 * PuckHandler
 *
 * PuckHandler handles pucks placed on Band1 or Band2.
 * There are queues for each segment on the band conveyor and for the whole
 * band conveyor, containing pucks placed on the band conveyor.
 *
 * @file PuckHandler.cpp
 * @author Chris Addo
 *         Jens Eberwein
 *         Tristan Rudat
 *         Martin Slowikowski
 * @date 2012-11-28
 * @version 0.6
 *
 */

#include "PuckHandler.h"

PuckHandler* PuckHandler::instance = NULL;
Mutex* PuckHandler::puckHandlerInstanceMutex = new Mutex();

PuckHandler::PuckHandler() {
	seg1Mutex = new Mutex;
	seg2Mutex = new Mutex;
	seg3Mutex = new Mutex;
	pucksBandMutex = new Mutex;
}

PuckHandler::~PuckHandler() {
	if (instance != NULL) {
		delete instance;
		instance = NULL;
		puckHandlerInstanceMutex->~Mutex();

		seg1Mutex->~Mutex();
		seg2Mutex->~Mutex();
		seg3Mutex->~Mutex();
		pucksBandMutex->~Mutex();
	}
}

PuckHandler* PuckHandler::getInstance() {
	if (!instance) {
		puckHandlerInstanceMutex->lock();
		if (!instance) {
			instance = new PuckHandler;
#ifdef DEBUG_PuckHandler
			printf("Debug PuckHandler: New PuckHandler instance created\n");
#endif
		}
		puckHandlerInstanceMutex->unlock();
	}

	return instance;
}


void PuckHandler::initializePucks(Dispatcher* disp) {
	for (int i = 0; i < MAX_PUCKS_BAND; i++) {
		pucks.push_back(new Controller(i + 1));
		disp->registerContextForAllFuncs(pucks.at(i));
#ifdef DEBUG_PuckHandler
		printf("Debug PuckHandler: created Puck%d \n", pucks.at(i)->getID());
#endif
	}
}

void PuckHandler::activatePuck() {
	if (!pucks.empty()) {
		for (int i = 0; i < MAX_PUCKS_BAND; i++) {
			if (!pucks.at(i)->isActive()) {
				pucks.at(i)->activate();
#ifdef DEBUG_PuckHandler
				printf("Debug PuckHandler: activated Puck%d \n", pucks.at(i)->getID());
#endif
				break;
			}
		}
	}
}


void PuckHandler::addPuckToBand(Controller* contr) {
	pucksBandMutex->lock();
	if (pucksOnBand1.size() < MAX_PUCKS_BAND) {
		pucksOnBand1.push_back(contr);
		pucksBandMutex->unlock();
	} else {
		pucksBandMutex->unlock();
		printf("Error PuckHandler: No moar space on Band1!\n");
	}
}

void PuckHandler::addPuckToSeg1(Controller* contr) {
	seg1Mutex->lock();
	pucksInSeg1.push(contr);
	seg1Mutex->unlock();
}

void PuckHandler::addPuckToSeg2(Controller* contr) {
	seg2Mutex->lock();
	pucksInSeg2.push(contr);
	seg2Mutex->unlock();
}

void PuckHandler::addPuckToSeg3(Controller* contr) {
	seg3Mutex->lock();
	pucksInSeg3.push(contr);
	seg3Mutex->unlock();
}


void PuckHandler::removePuckFromBand(Controller* contr) {
	pucksBandMutex->lock();
	if (!pucksOnBand1.empty()) {
		for (uint32_t i = 0; i < pucksOnBand1.size(); i++) {
			if (pucksOnBand1.at(i) == contr) {
				pucksOnBand1.erase(pucksOnBand1.begin() + i);
				break;
			}
		}
		pucksBandMutex->unlock();
	} else {
		pucksBandMutex->unlock();
		printf(
				"Error PuckHandler removePuckFromBand1(): Band1 already empty!\n");
	}
}

void PuckHandler::removePuckFromSeg1() {
	seg1Mutex->lock();
	if (!pucksInSeg1.empty()) {
		pucksInSeg1.pop();
		seg1Mutex->unlock();
	} else {
		seg1Mutex->unlock();
		printf("Error PuckHandler: Seg1 already empty!\n");
	}
}

void PuckHandler::removePuckFromSeg2() {
	seg2Mutex->lock();
	if (!pucksInSeg2.empty()) {
		pucksInSeg2.pop();
		seg2Mutex->unlock();
	} else {
		seg2Mutex->unlock();
		printf("Error PuckHandler: Seg2 already empty!\n");
	}
}

void PuckHandler::removePuckFromSeg3() {
	seg3Mutex->lock();
	if (!pucksInSeg3.empty()) {
		pucksInSeg3.pop();
		seg3Mutex->unlock();
	} else {
		seg3Mutex->unlock();
		printf("Error PuckHandler: Seg3 already empty!\n");
	}
}

bool PuckHandler::isBandEmpty() {
	pucksBandMutex->lock();
	return pucksOnBand1.empty();
	pucksBandMutex->unlock();
}

bool PuckHandler::isOnlyOneElemeOnBand() {
	pucksBandMutex->lock();
	return pucksOnBand1.size() == 1 ? true : false;
	pucksBandMutex->unlock();
}

bool PuckHandler::checkIfFirstElemInSeg1(Controller* contr) {
	seg1Mutex->lock();
	return (!pucksInSeg1.empty()) ? (pucksInSeg1.front() == contr) : false;
	seg1Mutex->unlock();
}

bool PuckHandler::checkIfFirstElemInSeg2(Controller* contr) {
	seg2Mutex->lock();
	return (!pucksInSeg2.empty()) ? (pucksInSeg2.front() == contr) : false;
	seg2Mutex->unlock();
}

bool PuckHandler::checkIfFirstElemInSeg3(Controller* contr) {
	seg3Mutex->lock();
	return (!pucksInSeg3.empty()) ? (pucksInSeg3.front() == contr) : false;
	seg3Mutex->unlock();
}

void PuckHandler::printQueueStatus() {
	printf("Queue Seg1 size(): %d -> PuckID: %d -> isFront: %c\n",
			pucksInSeg1.size(), (pucksInSeg1.empty() ? 50
					: pucksInSeg1.front()->getID()), (pucksInSeg1.empty() ? 'X'
					: pucksInSeg1.front()->isFirstElementInSegment() ? 't'
							: 'c'));
	printf("Queue Seg2 size(): %d -> PuckID: %d -> isFront: %c\n",
			pucksInSeg2.size(), (pucksInSeg2.empty() ? 50
					: pucksInSeg2.front()->getID()), (pucksInSeg2.empty() ? 'X'
					: pucksInSeg2.front()->isFirstElementInSegment() ? 't'
							: 'c'));
	printf("Queue Seg3 size(): %d -> PuckID: %d -> isFront: %c\n",
			pucksInSeg3.size(), (pucksInSeg3.empty() ? 50
					: pucksInSeg3.front()->getID()), (pucksInSeg3.empty() ? 'X'
					: pucksInSeg3.front()->isFirstElementInSegment() ? 't'
							: 'c'));
	printf("Queue Band size(): %d\n", pucksOnBand1.size());
}

void PuckHandler::reset(){

	seg1Mutex->~Mutex();
	seg2Mutex->~Mutex();
	seg3Mutex->~Mutex();
	pucksBandMutex->~Mutex();

	seg1Mutex = new Mutex;
	seg2Mutex = new Mutex;
	seg3Mutex = new Mutex;
	pucksBandMutex = new Mutex;

	pucks.clear();
	pucksOnBand1.clear();

	while(!pucksInSeg1.empty()) {
		pucksInSeg1.pop();
	}

	while(!pucksInSeg2.empty()) {
		pucksInSeg2.pop();
	}

	while(!pucksInSeg3.empty()) {
		pucksInSeg3.pop();
	}

	initializePucks(Dispatcher::getInstance());
}
