/**
 * SE2 WiSe 2012
 * RS232 (serial connection)
 *
 * Some bla bla bla for this file
 *
 * @file RS232.cpp
 * @author Chris Addo
 *         Jens Eberwein
 *         Tristan Rudat
 *         Martin Slowikowski
 * @date 2012-10-18
 * @version 0.1
 *
 */
//http://code.google.com/p/sep2-ss2012/source/browse/FestoProg/branches/old_continue/FestoProg/src/Communicator.h
//http://code.google.com/p/sep2-ss2012/source/browse/FestoProg/branches/old_continue/FestoProg/src/Communicator.cpp
//http://code.google.com/p/se2p/source/browse/Convayor/RS232.cpp
#include "RS232.h"

RS232* RS232::instance = NULL;
Mutex* RS232::RS232InstanceMutex = new Mutex();

RS232::RS232()
{
	recvbuf = 0;

	if((fd = open(DEV_SER1, O_RDWR)) < 0)
	{
		perror("opening devfile failed");
		exit(EXIT_FAILURE);
	}
}

RS232::~RS232()
{
	delete instance;
	instance = NULL;
	RS232InstanceMutex->~Mutex();
}

RS232* RS232::getInstance()
{
	RS232InstanceMutex->lock();

	if (instance == NULL)
	{
		instance = new RS232();
	}

	RS232InstanceMutex->unlock();

	return instance;
}

void RS232::execute(void* arg)
{
	while (!isStopped())
	{
		if ((read(fd, &recvbuf, sizeof(recvbuf))) < 0)
		{
			perror("recieving from devfile failed");
		}

		switch (recvbuf)
		{
		case MSG_TEST:
			printf("Testmessage recved");
			break;
		default:
			printf("Unknown msg recved");
		}

		recvbuf = 0;
	}

}

void RS232::shutdown()
{
	close(fd);
}

void RS232::sendMsg(char msg)
{
	if((write(fd, &msg, sizeof(msg))) < 0)
	{
		perror("writing on devfile failed");
	}
}
