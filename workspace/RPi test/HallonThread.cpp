/*
 * HallonThread.cpp
 *
 *  Created on: Apr 15, 2015
 *      Author: Jendrik
 */



#include "HallonThread.h"

using namespace std;

HallonThread::HallonThread() {
}

HallonThread::~HallonThread() {}

void* HallonThread::startThread(void* pVoid) {
	HallonThread* aThread = static_cast<HallonThread*>(pVoid);
	assert(aThread);
	aThread->result = aThread->run();
	aThread->setCompleted();
	return aThread->result;
}

void HallonThread::start() {
	int status = pthread_attr_init(&threadAttribute);
	if (status) {
		printError("pthread attribute init failed at", status,
				__FILE__,__LINE__);
		exit(status);
	}
	status = pthread_attr_setscope(&threadAttribute,
			PTHREAD_SCOPE_SYSTEM);
	if (status) {
		printError("pthread attribute setscope failed at", status,
				__FILE__,__LINE__);
		exit(status);
	}
	status = pthread_create(&threadId, &threadAttribute,
			HallonThread::startThread, (void*)this);
	if (status) {
		printError("pthread creation failed at", status,
				__FILE__,__LINE__);
		exit(status);
	}
	status = pthread_attr_destroy(&threadAttribute);
	if (status) {
		printError("pthread attribute destruction failed at", status,
				__FILE__,__LINE__);
		exit(status);
	}
}

void* HallonThread::join() {
	int status = pthread_join(threadId, NULL);
	if (status) {
		printError("pthread join failed at", status,
				__FILE__,__LINE__);
		exit(status);
	}
	return result;
}

void HallonThread::setCompleted() {};


void HallonThread::printError(char * msg, int status, char* fileName, int lineNumber) {
		cout << msg << " " << fileName << ":"
			 << lineNumber << "-" << status << endl;
}
