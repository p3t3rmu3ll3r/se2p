/*
 * PuckHandler.cpp
 *
 *  Created on: 24.11.2012
 *      Author: martin
 */

#include "PuckHandler.h"


PuckHandler* PuckHandler::instance = NULL;
Mutex* PuckHandler::puckHandlerInstanceMutex = new Mutex();


PuckHandler::PuckHandler() {

}

PuckHandler::~PuckHandler() {
	if (instance != NULL) {
		delete instance;
		instance = NULL;
		puckHandlerInstanceMutex->~Mutex();
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

	for(int i = 0 ; i < MAX_PUCKS_BAND1 ; i++) {
		pucks.push_back(new Controller(i+1));
		disp->registerContextForAllFuncs(pucks.at(i));

		if(pucks.at(i) != NULL){
			printf("Debug PuckHandler: created Puck%d \n", pucks.at(i)->getID());
		}
	}
}

void PuckHandler::activatePuck() {

	if(!pucks.empty()){
		for(int i = 0 ; i < MAX_PUCKS_BAND1 ; i++) {
			if(!pucks.at(i)->isActive()) {
				pucks.at(i)->activate();
				printf("Debug PuckHandler: activated Puck%d \n", pucks.at(i)->getID());
				break;
			}
		}
	}
}


void PuckHandler::addPuckToBand1(Controller* contr) {
	printf("i is adding ...size(): %d\n", pucksOnBand1.size());
	if (pucksOnBand1.size() < MAX_PUCKS_BAND1) {
		pucksOnBand1.push_back(contr);
	} else {
		printf("Error PuckHandler: No moar space on Band1!\n");
	}
	printf("i added ...\n");
}

void PuckHandler::addPuckToSeg1(Controller* contr){
	pucksInSeg1.push(contr);
}

void PuckHandler::addPuckToSeg2(Controller* contr){
	pucksInSeg2.push(contr);
}

void PuckHandler::addPuckToSeg3(Controller* contr){
	pucksInSeg3.push(contr);
}


void PuckHandler::removePuckFromBand1(Controller* contr){
	if(!pucksOnBand1.empty()){
		for(uint32_t i = 0; i < pucksOnBand1.size() ; i++){
			if(pucksOnBand1.at(i) == contr){
				pucksOnBand1.erase(pucksOnBand1.begin()+i);
				break;
			}
		}
	} else {
		printf("Error PuckHandler removePuckFromBand1(): Band1 already empty!\n");
	}
}

void PuckHandler::removePuckFromSeg1(){
	if(!pucksInSeg1.empty()){
		pucksInSeg1.pop();
	} else {
		printf("Error PuckHandler: Seg1 already empty!\n");
	}
}

void PuckHandler::removePuckFromSeg2(){
	if(!pucksInSeg2.empty()){
		pucksInSeg2.pop();
	} else {
		printf("Error PuckHandler: Seg2 already empty!\n");
	}
}

void PuckHandler::removePuckFromSeg3(){
	if(!pucksInSeg3.empty()){
		pucksInSeg3.pop();
	} else {
		printf("Error PuckHandler: Seg3 already empty!\n");
	}
}

bool PuckHandler::isBand1Empty(){
	return pucksOnBand1.empty();
}

//TODO methode EStop button(bool pressed)
/*
void PuckHandler::eStop(bool pressed){
	if(pressed){
		estop = true;
		ActorHAL::getInstance()->globalStop();
		ActorHAL::getInstance()->setSomeCoolLight();
		ActorHAL::getInstance()->gate(false);
		pauseAllTimer();
	} else {
		// estop bereits rausgezogen und reset gedrueckt
		estop = false;
		ActorHAL::getInstance()->globalUnstop();
		//ggf band leeren und alles auf anfang zurueck ...?! oder einfach weiterfahren
	}
}
*/

bool PuckHandler::isOnlyOneElemeOnBand1(){
	return pucksOnBand1.size() == 1 ? true : false;
}

bool PuckHandler::checkIfFirstElemInSeg1(Controller* contr){
	return (!pucksInSeg1.empty()) ? (pucksInSeg1.front() == contr) : false;
}

bool PuckHandler::checkIfFirstElemInSeg2(Controller* contr){
	return (!pucksInSeg2.empty()) ?  (pucksInSeg2.front() == contr) : false;
}

bool PuckHandler::checkIfFirstElemInSeg3(Controller* contr){
	return (!pucksInSeg3.empty()) ?  (pucksInSeg3.front() == contr) : false;
}
