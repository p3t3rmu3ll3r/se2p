/**
 * SE2 WiSe 2012
 * RS232 (serial connection)
 *
 * Some bla bla bla for this file
 *
 * @file RS232.h
 * @author Chris Addo
 *         Jens Eberwein
 *         Tristan Rudat
 *         Martin Slowikowski
 * @date 2012-10-18
 * @version 0.1
 *
 */

#ifndef RS232_H_
#define RS232_H_

#include <fcntl.h>

#include "HAWThread.h"
#include "Mutex.h"

#define DEV_SER1 "/dev/ser1"

#define MSG_TEST 'a'

class RS232: public thread::HAWThread {
private:
	static RS232* instance;
	static Mutex* RS232InstanceMutex;
	int fd;
	char recvbuf;

	RS232();

public:

	static RS232* getInstance();

	virtual ~RS232();
	void sendMsg(char msg);
	virtual void execute(void* arg);
	virtual void shutdown();
};
#endif /* RS232_H_ */
