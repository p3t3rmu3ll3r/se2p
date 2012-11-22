/*
 * Controller.cpp
 *
 *  Created on: 21.11.2012
 *      Author: aay973
 */

#include "Controller.h"

Controller::Controller() {

}

Controller::~Controller() {

}

void Controller::sbStartOpen(){state.sbStartOpen();}
void Controller::sbStartClosed(){state.sbStartClosed();}
void Controller::sbHeightcontrolOpen(){state.sbHeightcontrolOpen();}
void Controller::sbHeightcontrolClosed(){state.sbHeightcontrolOpen();}
void Controller::sbGateOpen(){state.sbGateOpen();}
void Controller::sbGateClosed(){state.sbGateClosed();}
void Controller::msMetalTrue(){state.sbGateClosed();}
void Controller::sbSlideOpen(){state.sbSlideOpen();}
void Controller::sbSlideClosed(){state.sbSlideClosed();}
void Controller::sbEndOpen(){state.sbSlideClosed();}
void Controller::sbEndClosed(){state.sbSlideClosed();}
void Controller::btnStartPressed(){state.btnStartPressed();}
void Controller::btnStartReleased(){state.btnStartReleased();}
void Controller::btnStopPressed(){state.btnStopPressed();}
void Controller::btnStopReleased(){state.btnStopReleased();}
void Controller::btnResetPressed(){state.btnResetPressed();}
void Controller::btnResetReleased(){state.btnResetReleased();}
void Controller::btnEstopPressed(){state.btnEstopPressed();}
void Controller::btnEstopReleased(){state.btnEstopReleased();}
