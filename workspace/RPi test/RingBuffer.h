/*
 * RingBuffer.h
 *
 *  Created on: Apr 13, 2015
 *      Author: Jendrik
 *      source: http://osix.net/modules/article/?id=464
 *      source-date: 13.04.15
 */
#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

#include <semaphore.h>
#include <pthread.h>

template<typename T>
class RingBuffer{

public:
	RingBuffer(int size, sem_t *readSemaphore){
		this->size = size;
		this->ringBuffer = new T[size];
		this->readerPoint = 0;
		this->writerPoint = 0;
		this->readSemaphore = readSemaphore;
		sem_init(&ownSemaphore,0,0);
		pthread_mutex_init(&accesMutex,NULL);
	}

	void writeElementToBuffer(T input) {
		pthread_mutex_lock(&accesMutex);
		if(writerPoint > size) writerPoint = 0;
		ringBuffer[writerPoint] = input;
		writerPoint++;
		if(writerPoint == readerPoint) readerPoint++;
		pthread_mutex_unlock(&accesMutex);
		sem_post(&ownSemaphore);
		sem_post(readSemaphore);
	}

	T getElement() {
		int result = sem_trywait(&ownSemaphore);
		if(!result) {
			T buffer;
			pthread_mutex_lock(&accesMutex);
			if(readerPoint == writerPoint) return NULL;
			buffer = ringBuffer[readerPoint];
			pthread_mutex_unlock(&accesMutex);
			return buffer;
		}
		return NULL;

	}

	T getNewestElement(){
		int result = sem_trywait(&ownSemaphore);
		if(!result) {
			pthread_mutex_lock(&accesMutex);
			if(readerPoint == writerPoint) return NULL;
			T buffer = ringBuffer[writerPoint-1];
			pthread_mutex_unlock(&accesMutex);
			return buffer;
		}
		return NULL;

	}

	~RingBuffer() {
		pthread_mutex_destroy(&accesMutex);
		delete ringBuffer;
	}

private:
	int size;
	T *ringBuffer;
	int writerPoint;
	int readerPoint;
	sem_t *readSemaphore;
	sem_t ownSemaphore;
	pthread_mutex_t accesMutex;


};




#endif
