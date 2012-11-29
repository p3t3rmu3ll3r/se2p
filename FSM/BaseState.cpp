/**
 * SE2 WiSe 2012
 * BaseState
 *
 * Represents a state in the used state pattern. All used states
 * are derived from this class.
 *
 * @file BaseState.h
 * @author Chris Addo
 *         Jens Eberwein
 *         Tristan Rudat
 *         Martin Slowikowski
 * @date 2012-11-22
 * @version 0.1
 *
 */

#include "BaseState.h"

BaseState::BaseState() {
	actorHAL = ActorHAL::getInstance();
	sensorHAL = SensorHAL::getInstance();
	puckHandler = PuckHandler::getInstance();
	errfsm = ErrorFSM::getInstance();
}

BaseState::~BaseState() {
	// TODO Auto-generated destructor stub
}

void BaseState::sbStartOpen(){}
void BaseState::sbStartClosed(){}
void BaseState::sbHeightcontrolOpen(){}
void BaseState::sbHeightcontrolClosed(){}
void BaseState::sbGateOpen(){}
void BaseState::sbGateClosed(){}
void BaseState::msMetalTrue(){}
void BaseState::sbSlideOpen(){}
void BaseState::sbSlideClosed(){}
void BaseState::sbEndOpen(){}
void BaseState::sbEndClosed(){}
void BaseState::btnStartPressed(){}
void BaseState::btnStartReleased(){}
void BaseState::btnStopPressed(){}
void BaseState::btnStopReleased(){}
void BaseState::btnResetPressed(){}
void BaseState::btnResetReleased(){}
void BaseState::btnEstopPressed(){}
void BaseState::btnEstopReleased(){}
