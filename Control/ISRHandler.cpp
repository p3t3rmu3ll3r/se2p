/**
 * SE2 WiSe 2012
 * ISR with pulse messages
 *
 *
 * \file ISRHandler.cpp
 * \author Chris Addo
 *         Jens Eberwein
 *         Tristan Rudat
 *         Martin Slowikowski
 * \date 2012-11-02
 * \version 0.1
 *
 */

#include "ISRHandler.h"

ISRHandler* ISRHandler::instance = NULL;
Mutex* ISRHandler::isrhandlerInstanceMutex = new Mutex();

ISRHandler::ISRHandler() {
	sHal = SensorHAL::getInstance();
	disp = Dispatcher::getInstance();
	dispatcherChid = disp->getChid();
	errfsmChid = errfsm->getErrorFSMChid();

	//Connect to channels
	if ((dispatcherCoid= ConnectAttach(0, 0, dispatcherChid, _NTO_SIDE_CHANNEL, 0)) == -1) {
		printf("ISRHandler: Error in ConnectAttach\n");
	}

	if ((errfsmCoid = ConnectAttach(0, 0, errfsmChid, _NTO_SIDE_CHANNEL, 0)) == -1) {
		printf("ISRHandler: Error in ConnectAttach\n");
	}
}

ISRHandler::~ISRHandler() {
	if (instance != NULL) {
		delete instance;
		instance = NULL;
		isrhandlerInstanceMutex->~Mutex();
	}
}

ISRHandler* ISRHandler::getInstance() {
	if (!instance) {
		isrhandlerInstanceMutex->lock();
		if (!instance) {
			instance = new ISRHandler;
#ifdef DEBUG_ISRHandler
			printf("Debug ISRHandler: New ISRHandler instance created\n");
#endif
		}
		isrhandlerInstanceMutex->unlock();
	}

	return instance;
}

void ISRHandler::execute(void*) {

	struct _pulse pulse;
	int oldVector = DEFAULT_ISR_VAL;
	int newVector = 0;
	int rc;
	int action = -1;

	while (!isStopped()) {
		rc = MsgReceivePulse(sHal->getChid(), &pulse, sizeof(pulse), NULL);
		if (rc < 0) {
			printf("ISRHandler: Error in recv pulse\n");
			if (isStopped()) {
				break;
			}
		}

		newVector = pulse.value.sival_int;
		int i;
		bool newVal;

		for (i = 0; i < 12; i++) {
			if (((newVector >> i) & 1) != ((oldVector >> i) & 1)) {
				newVal = (newVector >> i) & 1;

				switch (i) {
				case 0:
					if (newVal) {
#ifdef DEBUG_ISRHandler
						printf("Kein Werkstueck im Einlauf\n");
#endif
						action = SB_START_CLOSED;
					} else {
#ifdef DEBUG_ISRHandler
						printf("Werkstueck im Einlauf\n");
#endif
						action = SB_START_OPEN;
					}
					break;
				case 1:
					if (newVal) {
#ifdef DEBUG_ISRHandler
						printf("Kein Werkstueck in Hoehenmessung\n");
#endif
						action = SB_HEIGHTCONTROL_CLOSED;
					} else {
#ifdef DEBUG_ISRHandler
						printf("Werkstueck in Hoehenmessung\n");
#endif
						action = SB_HEIGHTCONTROL_OPEN;
					}
					break;
				case 2:
					//TODO diesen IRQ ignorieren, wenn IRQ WS in Hoehenmessung einfach getHeight()
					//generiert sonst diverse IRQs, brauchen wir nicht ...
					if (newVal) {
#ifdef DEBUG_ISRHandler
						printf("no pulse! Werkstueck im Toleranzbereich\n");
#endif
					} else {
#ifdef DEBUG_ISRHandler
						printf("no pulse! Werkstueck zu klein/gross\n");
#endif
					}
					break;
				case 3:
					if (newVal) {
#ifdef DEBUG_ISRHandler
						printf("Kein Werkstueck in Weiche\n");
#endif
						action = SB_GATE_CLOSED;
					} else {
#ifdef DEBUG_ISRHandler
						printf("Werkstueck in Weiche\n", i);
#endif
						action = SB_GATE_OPEN;
					}
					break;
				case 4:
					//TODO Wenn metall, dann IRQ == 1, Werkstueck weg dann IRQ == 0
					// kommt dann ein WS ohne metall, gibts KEIN irq, aufpassen!
					//solange also kein IRQ kommt == alles ok. wenn metall enthalten ist,
					//kommen zwei interrupts, dann auf band2!!!! handeln und den zweiten
					//irq ignorieren. Alternative, messen wie bei der hoehe.
					//TODO Metalsensor pollen, statt irq auswerten
					if (newVal) {
#ifdef DEBUG_ISRHandler
						printf("Werkstueck Metall\n");
#endif
						action = MS_METAL_TRUE;
					} else {
#ifdef DEBUG_ISRHandler
						printf("no pulse! Werkstueck kein Metall\n");
#endif
					}
					break;
				case 5:
					//TODO eigentlich auch not needed
					if (newVal) {
#ifdef DEBUG_ISRHandler
						printf("no pulse! Weiche offen\n");
#endif
					} else {
#ifdef DEBUG_ISRHandler
						printf("no pulse! Weiche geshlossen\n");
#endif
					}
					break;
				case 6:
					if (newVal) {
#ifdef DEBUG_ISRHandler
						printf("Rutsche nicht voll\n");
#endif
						action = SB_SLIDE_CLOSED;
					} else {
#ifdef DEBUG_ISRHandler
						printf("Rutsche voll\n");
#endif
						action = SB_SLIDE_OPEN;
					}
					break;
				case 7:
					if (newVal) {
#ifdef DEBUG_ISRHandler
						printf("kein Werkstueck im Auslauf\n");
#endif
						action = SB_END_CLOSED;
					} else {
#ifdef DEBUG_ISRHandler
						printf("Werkstueck im Auslauf\n");
#endif
						action = SB_END_OPEN;
					}
					break;
				case 8:
					if (newVal) {
#ifdef DEBUG_ISRHandler
						printf("Starttste gedrueck\n");
#endif
						action = BTN_START_PRESSED;
					} else {
#ifdef DEBUG_ISRHandler
						printf("Starttste losgelassen\n");
#endif
						action = BTN_START_RELEASED;
					}
					break;
				case 9:
					if (newVal) {
#ifdef DEBUG_ISRHandler
						printf("Stoptaste losgelassen\n");
#endif
						action = BTN_STOP_RELEASED;
					} else {
#ifdef DEBUG_ISRHandler
						printf("Stoptaste gedrueckt\n");
#endif
						action = BTN_STOP_PRESSED;
					}
					break;
				case 10:
					if (newVal) {
#ifdef DEBUG_ISRHandler
						printf("Resettaste gedrueckt\n");
#endif
						action = BTN_RESET_PRESSED;
					} else {
#ifdef DEBUG_ISRHandler
						printf("Resettaste losgelassen\n");
#endif
						action = BTN_RESET_RELEASED;
					}
					break;
				case 11:
					if (newVal) {
#ifdef DEBUG_ISRHandler
						printf("E-Stoptaste geloest\n");
#endif
						action = BTN_ESTOP_RELEASED;
					} else {
#ifdef DEBUG_ISRHandler
						printf("E-Stoptaste gedrueckt\n");
#endif
						action = BTN_ESTOP_PRESSED;
					}
					break;
				default:
					printf("no pulse! ISRTest switch def value\n");
				}

				//TODO pulse werden mom einfach an errorfsm und dispatcher geschickt.
				//TODO wenn error fsm arbeitet, soll dispatcher nix mehr tun ... hierrueber regeln oder im disp selber?!
				rc = MsgSendPulse(dispatcherCoid, SIGEV_PULSE_PRIO_INHERIT, PULSE_FROM_ISRHANDLER, action);
				if (rc < 0) {
					printf("ISRHandler: Error in MsgSendPulse");
				}

				rc = MsgSendPulse(errfsmCoid, SIGEV_PULSE_PRIO_INHERIT, PULSE_FROM_ISRHANDLER, action);
				if (rc < 0) {
					printf("ISRHandler: Error in MsgSendPulse");
				}
			}
		}
		oldVector = newVector;

	}
}
void ISRHandler::stop() {
	HAWThread::stop();
	sHal->stopInterrupt();

	if (ConnectDetach(dispatcherCoid) == -1) {
		printf("ISRHandler: Error in ConnectDetach\n");
	}

	if (ConnectDetach(errfsmCoid) == -1) {
		printf("ISRHandler: Error in ConnectDetach\n");
	}
}

void ISRHandler::shutdown() {
}
