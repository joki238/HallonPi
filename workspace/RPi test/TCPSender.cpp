/*
 * TCPSender.cpp
 *
 *  Created on: Apr 16, 2015
 *      Author: Jendrik
 */

#include "TCPSender.h"

TCPSender::TCPSender(const std::map<tcp::PackageType, void*> &bufferMap,
		int inputSocket, struct sockaddr_in remoteAddress,
		sem_t* tcpReadSemaphore) : HallonThread(),
		bufferMap(bufferMap), tcpReadSemaphore(tcpReadSemaphore),
		remoteAddress(remoteAddress) {
	this->inputSocket = inputSocket;
	this->adcBuffer = (RingBuffer<tcp::ADCCommunicationPackage> *) (bufferMap.at(tcp::ADC_COM));
	this->houseBuffer = (RingBuffer <tcp::HousekeepingCommunicationPackage> *) (bufferMap.at(tcp::HOUSE_COM));
}

void* TCPSender::run() {
	char buffer[500];
	bool dataSendable = true;
	int determineSendable;
	while(dataSendable) {
		sem_wait(tcpReadSemaphore);
		tcp::HousekeepingCommunicationPackage house;
		house = houseBuffer->getElement();
		if((int*)&house != NULL) {
			house.getFrame(buffer);
			determineSendable = send(inputSocket, &buffer, (size_t)house.getPackageLength(),0);
			std::cout << "Sended House" <<std::endl;
			if (determineSendable<=0) {
				dataSendable = false;
				continue;
			}
		}
		tcp::ADCCommunicationPackage adc;
		adc = adcBuffer->getElement();
		if((int*)&adc != NULL) {
			adc.getFrame(buffer);
			determineSendable = send(inputSocket, &buffer, (size_t)adc.getPackageLength(),0);
			std::cout << "Sended ADC" <<std::endl;
			if (determineSendable<=0) {
				dataSendable = false;
				continue;
			}
		}
	}
	return 0;
}

TCPSender::~TCPSender() {
	// TODO Auto-generated destructor stub
}

