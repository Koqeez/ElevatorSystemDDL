#include "SimulationTime.h"

SimulationTime* SimulationTime::instancePtr = 0;


SimulationTime::SimulationTime()
{
	this->time = 0;
}

SimulationTime::~SimulationTime()
{
}
SimulationTime* SimulationTime::getInstance() {
	if (!instancePtr) {
		instancePtr = new SimulationTime;
	}
	return instancePtr;
}
int SimulationTime::getTime() const {
	return time;
}
void SimulationTime::incrementTime() {
	this->time++;
}
void SimulationTime::setTime(const int time) {
	this->time = time;
}