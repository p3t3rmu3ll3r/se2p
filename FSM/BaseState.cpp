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

void BaseState::sbStartOpen(){/*puckHandler->incrementSenseorFuncCounter(SB_START_OPEN);*/}
void BaseState::sbStartClosed(){/*puckHandler->incrementSenseorFuncCounter(SB_START_CLOSED);*/}
void BaseState::sbHeightcontrolOpen(){puckHandler->incrementSenseorFuncCounter(SB_HEIGHTCONTROL_OPEN);}
void BaseState::sbHeightcontrolClosed(){/*puckHandler->incrementSenseorFuncCounter(SB_HEIGHTCONTROL_CLOSED);*/}
void BaseState::sbGateOpen(){puckHandler->incrementSenseorFuncCounter(SB_GATE_OPEN);}
void BaseState::sbGateClosed(){/*puckHandler->incrementSenseorFuncCounter(SB_GATE_CLOSED);*/}
void BaseState::msMetalTrue(){/*puckHandler->incrementSenseorFuncCounter(MS_METAL_TRUE);*/}
void BaseState::sbSlideOpen(){/*puckHandler->incrementSenseorFuncCounter(SB_SLIDE_OPEN);*/}
void BaseState::sbSlideClosed(){/*puckHandler->incrementSenseorFuncCounter(SB_SLIDE_CLOSED);*/}
void BaseState::sbEndOpen(){/*printf("Puck is incrementing --> SB_END_OPEN!!!111\n");*/puckHandler->incrementSenseorFuncCounter(SB_END_OPEN);}
void BaseState::sbEndClosed(){/*puckHandler->incrementSenseorFuncCounter(SB_END_CLOSED);*/}
void BaseState::btnStartPressed(){/*puckHandler->incrementSenseorFuncCounter(BTN_START_PRESSED);*/}
void BaseState::btnStartReleased(){/*puckHandler->incrementSenseorFuncCounter(BTN_START_RELEASED);*/}
void BaseState::btnStopPressed(){/*puckHandler->incrementSenseorFuncCounter(BTN_STOP_PRESSED);*/}
void BaseState::btnStopReleased(){/*puckHandler->incrementSenseorFuncCounter(BTN_STOP_RELEASED);*/}
void BaseState::btnResetPressed(){/*puckHandler->incrementSenseorFuncCounter(BTN_RESET_PRESSED);*/}
void BaseState::btnResetReleased(){/*puckHandler->incrementSenseorFuncCounter(BTN_RESET_RELEASED);*/}
void BaseState::btnEstopPressed(){/*puckHandler->incrementSenseorFuncCounter(BTN_ESTOP_PRESSED);*/}
void BaseState::btnEstopReleased(){/*puckHandler->incrementSenseorFuncCounter(BTN_ESTOP_RELEASED);*/}

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























