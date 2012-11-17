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

	//Connect to channel
	if ((coid = ConnectAttach(0, 0, dispatcherChid, _NTO_SIDE_CHANNEL, 0))
			== -1) {
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
			printf("Debug Dispatcher: New Dispatcher instance created\n");
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
						printf("Kein Werkstueck im Einlauf\n");
						action = SB_START_CLOSED;
					} else {
						printf("Werkstueck im Einlauf\n");
						action = SB_START_OPEN;
					}
					break;
				case 1:
					if (newVal) {
						printf("Kein Werkstueck in Hoehenmessung\n");
						action = SB_HEIGHTCONTROL_OPEN;
					} else {
						printf("Werkstueck in Hoehenmessung\n");
						action = SB_HEIGHTCONTROL_CLOSED;
					}
					break;
				case 2:
					//TODO diesen IRQ ignorieren, wenn IRQ WS in Hoehenmessung einfach getHeight()
					//generiert sonst diverse IRQs, brauchen wir nicht ...
					if (newVal) {
						printf("no pulse! Werkstueck im Toleranzbereich\n");
					} else {
						printf("no pulse! Werkstueck zu klein/gross\n");
					}
					break;
				case 3:
					if (newVal) {
						printf("Kein Werkstueck in Weiche\n");
						action = SB_GATE_CLOSED;
					} else {
						printf("Werkstueck in Weiche\n", i);
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
						printf("Werkstueck Metall\n");
						action = MS_METAL_TRUE;
					} else {
						printf("no pulse! Werkstueck kein Metall\n");
					}
					break;
				case 5:
					//TODO eigentlich auch not needed
					if (newVal) {
						printf("no pulse! Weiche offen\n");
					} else {
						printf("no pulse! Weiche geshlossen\n");
					}
					break;
				case 6:
					if (newVal) {
						printf("Rutsche nicht voll\n");
						action = SB_SLIDE_CLOSED;
					} else {
						printf("Rutsche voll\n");
						action = SB_SLIDE_OPEN;
					}
					break;
				case 7:
					if (newVal) {
						printf("kein Werkstueck im Auslauf\n");
						action = SB_END_CLOSED;
					} else {
						printf("Werkstueck im Auslauf\n");
						action = SB_END_OPEN;
					}
					break;
				case 8:
					if (newVal) {
						printf("Starttste gedrueck\n");
						action = BTN_START_PRESSED;
					} else {
						printf("Starttste losgelassen\n");
						action = BTN_START_RELEASED;
					}
					break;
				case 9:
					if (newVal) {
						printf("Stoptaste losgelassen\n");
						action = BTN_STOP_RELEASED;
					} else {
						printf("Stoptaste gedrueckt\n");
						action = BTN_STOP_PRESSED;
					}
					break;
				case 10:
					if (newVal) {
						printf("Resettaste gedrueckt\n");
						action = BTN_RESET_PRESSED;
					} else {
						printf("Resettaste losgelassen\n");
						action = BTN_RESET_RELEASED;
					}
					break;
				case 11:
					//TODO schalter prellt beim rausziehen ... loest zig mal IRQs aus, entprellen
					//z.B.wenn not aus ISR ausgeloest, not aus ignorieren, beim ersten mal einfach
					//n bool setzen, den erst wieder ruecksetzen, wenn start gedrueckt wird.
					//start prueft dann, ob not aus freigegeben ist und startet erst DANN wieder.
					if (newVal) {
						printf("E-Stoptaste geloest\n");
						action = BTN_ESTOP_RELEASED;
					} else {
						printf("E-Stoptaste gedrueckt\n");
						action = BTN_ESTOP_PRESSED;
					}
					break;
				default:
					printf("no pulse! ISRTest switch def value\n");
				}

				rc = MsgSendPulse(coid, SIGEV_PULSE_PRIO_INHERIT, PULSE_FROM_ISRHANDLER, action);
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

	if (ConnectDetach(coid) == -1) {
		printf("ISRHandler: Error in ConnectDetach\n");
	}
}

void ISRHandler::shutdown() {
}
