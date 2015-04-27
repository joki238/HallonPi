/*
 * HousekeepingCollector.cpp
 *
 *  Created on: Apr 15, 2015
 *      Author: Jendrik
 */

#include "HousekeepingCollector.h"

const std::string HousekeepingCollector::readpath = std::string("/proc/stat");

HousekeepingCollector::HousekeepingCollector(
		RingBuffer<tcp::HousekeepingCommunicationPackage> *houseBuffer) :
		HallonThread(), houseBuffer(houseBuffer) {
	usage = 0;
	usageBuffer = 0;
	cpuLoad = 0;
}

void* HousekeepingCollector::run() {
	std::ifstream housestream;
	std::string line;
	int buffer;
	usageBuffer = 0;
	housestream.open(readpath.c_str());
	std::getline(housestream, line);
	buffer = line.find(' ',0);
	usageBuffer += atof((line.substr(buffer)).c_str());
	buffer = line.find_first_not_of(' ', buffer);
	buffer = line.find(' ',buffer);
	usageBuffer += atof((line.substr(buffer)).c_str());
	buffer = line.find_first_not_of(' ', buffer);
	buffer = line.find(' ',buffer);
	usageBuffer += atof((line.substr(buffer)).c_str());
	sleep(1);
	while(runBool) {
		usage = 0;
		housestream.open(readpath.c_str());
		std::getline(housestream, line);
		buffer = line.find(' ',0);
		usage += atof((line.substr(buffer)).c_str());
		buffer = line.find_first_not_of(' ', buffer);
		buffer = line.find(' ',buffer);
		usage += atof((line.substr(buffer)).c_str());
		buffer = line.find_first_not_of(' ', buffer);
		buffer = line.find(' ',buffer);
		usage += atof((line.substr(buffer)).c_str());
		cpuLoad = 1.*(usage - usageBuffer) / 400.;
		usageBuffer = usage;
		tcp::HousekeepingCommunicationPackage house = tcp::HousekeepingCommunicationPackage(time(NULL), cpuLoad);
		houseBuffer->writeElementToBuffer(house);
		housestream.close();
		sleep(1);
	}
	return 0;
}


HousekeepingCollector::~HousekeepingCollector() {
	// TODO Auto-generated destructor stub
}

