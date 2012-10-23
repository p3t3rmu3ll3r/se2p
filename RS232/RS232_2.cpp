/**
 * SE2 WiSe 2012
 * RS232 (serial connection) for /dev/ser2
 *
 * Reading on COM-port is implemented as a thread with qnx function readcond.
 * readcond generates cyclic timeouts, therefore after calling the thread's stop()
 * function the main-thread is not blocking within the thread's join() function.
 * Sending messages works without a thread.
 *
 * \file RS232_2.cpp
 * \author Chris Addo
 *         Jens Eberwein
 *         Tristan Rudat
 *         Martin Slowikowski
 * \date 2012-10-18
 * \version 0.1
 *
 */

#include "RS232_2.h"

RS232_2* RS232_2::instance = NULL;
Mutex* RS232_2::RS232InstanceMutex = new Mutex();

RS232_2::RS232_2()
{
	recvbuf = 0;
	struct termios ts;

	if((fd = open(DEV_SER2, O_RDWR)) < 0)
	{
		printf("Debug RS232_2: opening devfile2 failed\n");
		exit(EXIT_FAILURE);
	} else {
#ifdef DEBUG_RS232
		printf("Debug RS232_2: opening devfile2 SUCCESSED\n");
#endif
	}

	// flushes data received but not read and
	// data written but not transmitted
	tcflush(fd, TCIOFLUSH);

	sleep(1);

	// Einstellung der Schnittstelle holen
	tcgetattr(fd, &ts);

	// Input/Output Datenrate setzen
	cfsetispeed(&ts, B115200);
	cfsetospeed(&ts, B115200);

	// Schnittstelle konfigurieren
	ts.c_cflag &= ~CSIZE;	// clear number of data bits
	ts.c_cflag &= ~CSTOPB;	// 2 stop bits
	ts.c_cflag &= ~PARENB;	// no parity bit
	ts.c_cflag |= CS8;		// 8 Data bits
	ts.c_cflag |= CREAD;	// enable receiving characters
	ts.c_cflag |= CLOCAL;	// local connection, no modem contol

	// Einstellungen sofort uebernehmen
	tcsetattr(fd, TCSANOW, &ts);
}

RS232_2::~RS232_2()
{
	delete instance;
	instance = NULL;
	RS232InstanceMutex->~Mutex();
	if(close(fd) < 0){
		printf("error closing (RS232_2) fd\n");
	}
}

RS232_2* RS232_2::getInstance()
{
	if (!instance) {
		RS232InstanceMutex->lock();
		if (!instance) {
			instance = new RS232_2;
#ifdef DEBUG_RS232
			printf("Debug RS232_2: New RS232_2 instance created\n");
#endif
		}
		RS232InstanceMutex->unlock();
	}
	return instance;
}

void RS232_2::execute(void* arg)
{
	int lenRead = 0;
	while (!isStopped()) {
		if ((lenRead = readcond(fd, &recvbuf, sizeof(recvbuf), 1, 0, 10)) < 0) {
			printf("recieving from devfile failed\n");
		}

		if(lenRead <= 0) {
			if(errno == EAGAIN || lenRead == 0){
#ifdef DEBUG_RS232
			printf("Debug RS232_2: Timeout or EAGAIN\n");
#endif
			}
		}

		switch (recvbuf) {
		case MSG_TEST:
			printf("Testmessage recved: %c\n", recvbuf);
			break;
		case MSG_TIMEOUT:
#ifdef DEBUG_RS232
			printf("Debug RS232_2: Timeout recved\n");
#endif
			break;
		default:
#ifdef DEBUG_RS232
			printf("Debug RS232_2: Unknown msg recved: %c\n", recvbuf);
#endif
			break;
		}

		recvbuf = 0;
	}
}

void RS232_2::shutdown()
{
}

void RS232_2::sendMsg(char msg)
{
	if((write(fd, &msg, sizeof(msg))) < 0)
	{
		printf("writing on devfile failed\n");
	}
}

