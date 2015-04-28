/*
 * TCPSender.h
 *
 *  Created on: Apr 16, 2015
 *      Author: Jendrik
 */

#ifndef TCPSENDER_H_
#define TCPSENDER_H_

#include "HallonThread.h"
#include "RingBuffer.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <semaphore.h>
#include <map>

#include "Global.h"
extern bool runBool;

class TCPSender: public HallonThread {
public:
	TCPSender(const std::map<tcp::PackageType, void*> &bufferMap,
			int inputSocket, struct sockaddr_in remoteAddress,
			sem_t* tcpReadSemaphore);
	virtual ~TCPSender();

private:
	int inputSocket;
	struct sockaddr_in remoteAddress;
	const std::map<tcp::PackageType, void*> bufferMap;
	sem_t* tcpReadSemaphore;
	RingBuffer<tcp::ADCCommunicationPackage> *adcBuffer;
	RingBuffer<tcp::HousekeepingCommunicationPackage> *houseBuffer;
	void* run();

};

#endif /* TCPSENDER_H_ */
