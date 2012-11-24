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

	/* whyyyy??? so serious?!?!?

	while (!this->elemsOnBand1.empty())
	{
		this->elemsOnBand1.pop();
	}

	while (!this->elemsInSeg1.empty())
	{
		this->elemsInSeg1.pop();
	}

	while (!this->elemsInSeg2.empty())
	{
		this->elemsInSeg2.pop();
	}

	while (!this->elemsInSeg3.empty())
	{
		this->elemsInSeg3.pop();
	}

	*/
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


void PuckHandler::addPuckToBand1(Controller* contr) {
	if (elemsOnBand1.size() < MAX_PUCKS_BAND1) {
		elemsOnBand1.push(contr);
	} else {
		printf("Error PuckHandler: No moar space on Band1!\n");
	}
}

void PuckHandler::addPuckToSeg1(Controller* contr){
	elemsInSeg1.push(contr);
}

void PuckHandler::addPuckToSeg2(Controller* contr){
	elemsInSeg2.push(contr);
}

void PuckHandler::addPuckToSeg3(Controller* contr){
	elemsInSeg3.push(contr);
}


void PuckHandler::removePuckFromBand1(){
	if(elemsOnBand1.size() != 0){
		elemsOnBand1.pop();
	} else {
		printf("Error PuckHandler: Band1 already empty!\n");
	}
}

void PuckHandler::removePuckFromSeg1(){
	elemsInSeg1.pop();
}

void PuckHandler::removePuckFromSeg2(){
	elemsInSeg2.pop();
}

void PuckHandler::removePuckFromSeg3(){
	elemsInSeg3.pop();
}


bool PuckHandler::isBand1Empty(){
	return (elemsOnBand1.empty());
}

bool PuckHandler::checkIfFirstElemInSeg1(Controller* contr){
	return (elemsInSeg1.front() == contr); //TODO: todo... -.-
}

bool PuckHandler::checkIfFirstElemInSeg2(Controller* contr){
	return (elemsInSeg2.front() == contr);
}

bool PuckHandler::checkIfFirstElemInSeg3(Controller* contr){
	return (elemsInSeg3.front() == contr);
}
