/*
 * CommandCommunicationPackage.h
 *
 *  Created on: Apr 27, 2015
 *      Author: Jendrik
 */

#ifndef COMMANDCOMMUNICATIONPACKAGE_H_
#define COMMANDCOMMUNICATIONPACKAGE_H_

#include "CommunicationPackage.h"
#include "CommandNumber.h"
#include "PackageType.h"

namespace tcp{

class CommandCommunicationPackage: public CommunicationPackage {
public:
	CommandCommunicationPackage();
	CommandCommunicationPackage(const char *frame);
	CommandCommunicationPackage(unsigned int timestamp,
			CommandNumber commandNumber, double parameter);

	CommandNumber getCommandNumber();
	double getParameter();


private:
	CommandNumber commandNumber;
	double parameter;

	static const unsigned short packageLength;
	static const PackageType packageType;
	static const unsigned short commandNumberPosition;
	static const unsigned short parameterPosition;

	CommandNumber readCommandNumber();
	bool writeCommandNumber(CommandNumber commandNumber);

	double readParameter();
	bool writeParameter(double parameter);

};
}

#endif /* COMMANDCOMMUNICATIONPACKAGE_H_ */
