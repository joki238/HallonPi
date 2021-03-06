/*
 * ADCCommunicationPackage.cpp
 *
 *  Created on: Apr 12, 2015
 *      Author: Jendrik
 */

#include "./ADCCommunicationPackage.h"

namespace tcp {

const unsigned short ADCCommunicationPackage::adcValuePosition = 10;
const unsigned short ADCCommunicationPackage::packageLength = 14;
const PackageType ADCCommunicationPackage::packageType = ADC_COM;


ADCCommunicationPackage::ADCCommunicationPackage(char *frame):
		CommunicationPackage(frame, ADC_COM, packageLength) {
	if(!valid) {
		this->adcValue = 0;
	}
	else{
		this->adcValue = readADCValue();
	}
}

ADCCommunicationPackage::ADCCommunicationPackage():CommunicationPackage() {
	this->adcValue = 0;
}

ADCCommunicationPackage::ADCCommunicationPackage(unsigned int timestamp, unsigned short adcValue):
	CommunicationPackage(ADC_COM, timestamp, packageLength){
	this->adcValue = adcValue;

	if(!writeADCValue(this->adcValue)) valid = false;
}

bool ADCCommunicationPackage::writeADCValue(unsigned short value) {
	if(adcValuePosition+2>packageLength) return false;
	uShort2Char(value, &frame[adcValuePosition]);
	return true;
}



unsigned short ADCCommunicationPackage::getADCValue() const {
	return this->adcValue;
}

unsigned short ADCCommunicationPackage::readADCValue() {
	return char2UShort(&frame[adcValuePosition]);
}

}



