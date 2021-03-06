/*
 * ADCCommunicationPackage.h
 *
 *  Created on: Apr 12, 2015
 *      Author: Jendrik
 */

#ifndef ADCCOMMUNICATIONPACKAGE_H_
#define ADCCOMMUNICATIONPACKAGE_H_

#include "./CommunicationPackage.h"

namespace tcp {

class ADCCommunicationPackage : public CommunicationPackage {

public:
	ADCCommunicationPackage();
	ADCCommunicationPackage(char *frame);
	ADCCommunicationPackage(unsigned int timestamp, unsigned short adcValue);

	unsigned short getADCValue() const;


private:

	unsigned short adcValue;
	static const unsigned short packageLength;
	static const PackageType packageType;

	static const unsigned short adcValuePosition;
	bool writeADCValue(unsigned short value);
	unsigned short readADCValue();


};

}

#endif /* ADCCOMMUNICATIONPACKAGE_H_ */
