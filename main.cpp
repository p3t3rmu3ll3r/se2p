/**
 * SE2 WiSe 2012
 * main class
 *
 * @file main.cpp
 * @author Chris Addo
 *         Jens Eberwein
 *         Tristan Rudat
 *         Martin Slowikowski
 * @date 2012-10-23
 * @version 0.2
 * 
 */

#include <cstdlib>
#include <iostream>
#include <unistd.h>

#include "Tests/HALTest.h"
#include "Tests/RS232Test.h"
#include "LightController.h"
#include "Tests/LightControllerTest.h"
#include "Sensor.h"



int main(int argc, char *argv[]) {

	//MyObject* myObject = new MyObject();
	//myObject->myMethod();
	//delete myObject;

	//thread::MyThread thread;
	//thread.start(NULL);

	//Testing Milestone 2
	//HALTest halTest;
	//halTest.testHal();

	//RS232Test rs232Test;
	//rs232Test.testRS232();

	// Testing Milestone 3
	LightController* lc = LightController::getInstance();
	lc->start(0);
	lc->hold();
	//LightControllerTest lctest;
	//lctest.testLightController();

	Sensor sensor;
	//int coid = ConnectAttach(0, 0, sensor.getChid(), _NTO_SIDE_CHANNEL, 0);
	HAL* hal = HAL::getInstance();

	struct _pulse pulse;
	int oldVal = DEFAULT_ISR_VAL;
	int newVal = 0;
	int height = 0;
	bool accepted = false;
	bool turnOver = false;

	while(1){
		int rc = MsgReceivePulse(sensor.getChid(), &pulse, sizeof(pulse), NULL);
		if(rc < 0) {
			printf("Error in recv pulse\n");
		}

		printf("ISR status: %x\n", pulse.value.sival_int);
		newVal = pulse.value.sival_int;
		int i;
		for(i = 0; i < 12; i++){
			if(((newVal >> i) & 1) != ((oldVal >> i) & 1)){
				switch(i){
					case 0:
						if((newVal >> i) & 1){
							//hal->engineStop();
						} else {
							if(((newVal >> 7) & 1)) {
								lc->lightsOff();
								hal->engineUnstop();
								hal->engineRight(false);
							}
						}
					break;
					case 1:
						if((newVal >> i) & 1){
						} else {
							hal->engineStop();
							height = sensor.getHeight();
							if(height > 3300 && height < 3700){
								accepted = true;
								printf("Accepted: %i // Height: %i\n", accepted, height);
							}
							if(height > 2300 && height < 2600){
								turnOver = true;
								printf("turnOver: %i // Height: %i\n", turnOver, height);
							}
						hal->engineUnstop();
						}
					break;
					case 3:
						if((newVal >> i) & 1){
						} else {
							hal->gate(accepted | turnOver);
							accepted = false;
						}
					break;
					case 6:
						if((newVal >> i) & 1){
						} else {
							hal->engineStop();
						}
					break;
					case 7:
						if((newVal >> i) & 1){
							if(!((newVal >> 0) & 1)) {
								lc->lightsOff();
								hal->engineUnstop();
								hal->engineRight(false);
							}
						} else {
							hal->engineStop();
							hal->gate(false);
							if(turnOver){
								lc->manualTurnover();
								turnOver = false;
							}
						}
					break;
				}
			}
		}
		oldVal = newVal;
	}

	return EXIT_SUCCESS;
}
