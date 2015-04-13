/*
 * RingBuffer.h
 *
 *  Created on: Apr 13, 2015
 *      Author: Jendrik
 */
#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

template<typename T>
class RingBuffer {

public:
	RingBuffer(int size) {
		this->size = size;
		this->ringBuffer = new T[size];
		this->readable = false;
		this->readerPoint = 0;
		this->writerPoint = 0;
	}

	void writeElementToBuffer(T input) {
		if(writerPoint > size) writerPoint = 0;
		ringBuffer[writerPoint] = input;
		writerPoint++;
		if(writerPoint == readerPoint) readerPoint++;
		if(!readable) readable = true;
	}

	T getElement() {
		if(readerPoint == writerPoint) return -1;
		T buffer;
		buffer = ringBuffer[readerPoint];
		if(readerPoint++==writerPoint) readable = false;
		return buffer;
	}

	T getNewestElement(){
		if(readerPoint == writerPoint) return -1;
		return ringBuffer[writerPoint-1];
	}

	bool dataToRead(){
		return readable;
	}

	~RingBuffer() {
		delete ringBuffer;
	}

private:
	int size;
	T *ringBuffer;
	int writerPoint;
	int readerPoint;
	bool readable;


};




#endif