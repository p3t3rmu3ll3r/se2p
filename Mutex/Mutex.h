/**
 * SE2 WiSe 2012
 * pThread Mutex
 *
 * Some bla bla bla for this file
 * 
 * @file Mutex.h
 * @author Chris Addo
 *         Jens Eberwein
 *         Tristan Rudat
 *         Martin Slowikowski
 * @date 2012-10-18
 * @version 0.1
 * 
 */

#ifndef MUTEX_H_
#define MUTEX_H_

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

class Mutex {
public:
	/**
	 * Constructor for mutex initialization.
	 * The pthread_mutex_init function initializes the given mutex with the given attributes.
	 * If attr is null, then the default attributes are used.
	 */
	Mutex();

	/**
	 * Destructor for mutex destroying
	 * The pthread_mutex_destroy function destroys the given mutex.
	 * If the mutex is already destroyed, then errno is set to EINVAL.
	 * If the mutex is locked, then errno is set to EBUSY.
	 */
	virtual ~Mutex();

	/*
	 * function locks the given mutex.
	 * If the mutex is already locked, then the calling thread blocks until the thread that
	 * currently holds the mutex unlocks it.
	 */
	void lock();

	/**
	 * function unlocks the given mutex.
	 */
	void unlock();

private:
	pthread_mutex_t mutex;
};

#endif /* MUTEX_H_ */
