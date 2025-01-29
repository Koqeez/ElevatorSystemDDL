#pragma once
#ifndef SIMULATION_TIME_H
#define SIMULATION_TIME_H

class SimulationTime
{
public:
	SimulationTime();
	~SimulationTime();
	SimulationTime* getInstance();
	
	int getTime() const;
	void incrementTime();

	void setTime(const int time);

	static SimulationTime* instancePtr;
	int time;
private:

};

#endif // !SIMULATION_TIME_H
