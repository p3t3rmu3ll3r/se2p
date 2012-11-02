/*
 * ISRTest.cpp
 *
 *  Created on: 29.10.2012
 *      Author: martin
 */


#include "ISRTest.h"

ISRTest::ISRTest() {
}

ISRTest::~ISRTest() {
}

void ISRTest::execute(void*) {
	SensorHAL* sHal = SensorHAL::getInstance();
	ActorHAL* aHal = ActorHAL::getInstance();

	struct _pulse pulse;
	int oldVal = DEFAULT_ISR_VAL;
	int newVal = 0;
	int rc;

	while (!isStopped()) {
		rc = MsgReceivePulse(sHal->getChid(), &pulse, sizeof(pulse), NULL);
		if (rc < 0) {
			printf("Error in recv pulse\n");
			if (isStopped()) {
				break;
			}
		}

		printf("ISR status: %x\n", pulse.value.sival_int);

		newVal = pulse.value.sival_int;
		int i;

		for (i = 0; i < 12; i++) {
			if (((newVal >> i) & 1) != ((oldVal >> i) & 1)) {
				//TODO fuer die einzelnen Faelle DEFINEs oder enums machen, brauchen
				//wir eh fuer die states spaeter
				switch (i) {
				case 0:
					if ((newVal >> i) & 1) {
						printf("Kein Werkstueck im Einlauf\n");
					} else {
						printf("Werkstueck im Einlauf\n");
						aHal->engineRight(false);
						aHal->engineUnstop();
					}
				break;
				case 1:
					if ((newVal >> i) & 1) {
						printf("Kein Werkstueck in Hoehenmessung\n");
					} else {
						printf("Werkstueck in Hoehenmessung\n");
					}
				break;
				case 2:
					//TODO diesen IRQ ignorieren, wenn IRQ WS in Hoehenmessung einfach getHeight()
					//generiert sonst diverse IRQs, brauchen wir nicht ...
					if ((newVal >> i) & 1) {
						printf("Werkstueck im Toleranzbereich: %d\n", sHal->getHeight());
					} else {
						printf("Werkstueck zu klein/gross: %d\n", sHal->getHeight());
					}
				break;
				case 3:
					if ((newVal >> i) & 1) {
						printf("Kein Werkstueck in Weiche\n");
					} else {
						aHal->gate(true);
						printf("Werkstueck in Weiche\n", i);
					}
				break;
				case 4:
					//TODO Wenn metall, dann IRQ == 1, Werkstueck weg dann IRQ == 0
					// kommt dann ein WS ohne metall, gibts KEIN irq, aufpassen!
					if ((newVal >> i) & 1) {
						printf("Werkstueck Metall\n");
					} else {
						printf("Werkstueck kein Metall\n");
					}
				break;
				case 5:
					if ((newVal >> i) & 1) {
						printf("Weiche offen\n");
					} else {
						printf("Weiche geshlossen\n");
					}
				break;
				case 6:
					if ((newVal >> i) & 1) {
						printf("Rutsche nicht voll\n");
					} else {
						printf("Rutsche voll\n");
					}
				break;
				case 7:
					if ((newVal >> i) & 1) {
						printf("kein Werkstueck im Auslauf\n");
					} else {
						aHal->gate(false);
						aHal->engineStop();
						printf("Werkstueck im Auslauf\n");
					}
				break;
				case 8:
					if ((newVal >> i) & 1) {
						printf("Starttste gedrueck\n");
					} else {
						printf("Starttste losgelassen\n");
					}
				break;
				case 9:
					if ((newVal >> i) & 1) {
						printf("Stoptaste losgelassen\n");
					} else {
						printf("Stoptaste gedrueckt\n");
					}
				break;
				case 10:
					if ((newVal >> i) & 1) {
						printf("Resettaste gedrueckt\n");
					} else {
						printf("Resettaste losgelassen\n");
					}
				break;
				case 11:
					//TODO schalter prellt beim rausziehen ... loest zig mal IRQs aus, entprellen
					if ((newVal >> i) & 1) {
						printf("E-Stoptaste geloest\n");
					} else {
						printf("E-Stoptaste gedrueckt\n");
					}
				break;
				default:
					printf("ISRTest switch def value\n");
				}
			}
		}
		oldVal = newVal;
	}
}

void ISRTest::shutdown() {
}
