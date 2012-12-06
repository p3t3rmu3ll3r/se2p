/**
 * SE2 WiSe 2012
 * BaseState
 *
 * Represents a state in the used state pattern. All used states
 * are derived from this class.
 *
 * @file BaseState.cpp
 * @author Chris Addo
 *         Jens Eberwein
 *         Tristan Rudat
 *         Martin Slowikowski
 * @date 2012-12-01
 * @version 0.2
 *
 */

#include "BaseState.h"

BaseState::BaseState() {
	actorHAL = ActorHAL::getInstance();
	sensorHAL = SensorHAL::getInstance();
	puckHandler = PuckHandler::getInstance();
	errfsm = ErrorFSM::getInstance();
	rs232_1 = RS232_1::getInstance();
	timerHandler = TimerHandler::getInstance();
}

BaseState::~BaseState() {
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

void BaseState::rs232Band2Ack(){}
void BaseState::rs232Band2Ready(){}
void BaseState::rs232Band1Waiting(){}
void BaseState::rs232PuckArrivedOnBand2(){}

void BaseState::timerGateClose(){}
void BaseState::timerSlideFull(){}
void BaseState::timerSeg1Min(){}
void BaseState::timerSeg1Max(){}
void BaseState::timerSeg2Min(){}
void BaseState::timerSeg2Max(){}
void BaseState::timerSeg3Min(){}
void BaseState::timerSeg3Max(){}























