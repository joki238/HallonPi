/*
 * TCPReceiver.cpp
 *
 *  Created on: Apr 27, 2015
 *      Author: Jendrik
 */

#include "TCPReceiver.h"
#define COMMANDLENGTH 20


TCPReceiver::TCPReceiver(int inputSocket, struct sockaddr_in remoteAddress,
		RingBuffer<tcp::CommandCommunicationPackage>* commandBuffer,
		sem_t* commandSemaphore) :
		HallonThread(), commandBuffer(commandBuffer), remoteAddress(remoteAddress),
		inputSocket(inputSocket), commandSemaphore(commandSemaphore) {
	buffer = new char[1000];
}

TCPReceiver::~TCPReceiver() {
	// TODO Auto-generated destructor stub
}

void* TCPReceiver::run() {
	tcp::CommandCommunicationPackage commandPackage;
	unsigned int startReading;
	char charBuffer[500];
	memset(charBuffer,'\0',500);
	while(recv(inputSocket, charBuffer, (size_t)COMMANDLENGTH, 0)) {
		buffer.append(charBuffer);
		startReading = buffer.find(tcp::CommunicationPackage::starting);
		if(startReading!=std::string::npos ) {
			buffer.erase(0,startReading);
			if((buffer.length()-COMMANDLENGTH) < 0) {
				memset(charBuffer,'\0',500);
				recv(inputSocket, charBuffer, (size_t)(COMMANDLENGTH-buffer.length()), 0);
				buffer.append(charBuffer);
			}
			commandPackage = tcp::CommandCommunicationPackage(buffer.data());
			if(commandPackage.isValid()) {
				commandBuffer->writeElementToBuffer(commandPackage);
			}
			buffer.erase(0,COMMANDLENGTH);
		}
		memset(charBuffer,'\0',500);
	}
	return 0;
}
