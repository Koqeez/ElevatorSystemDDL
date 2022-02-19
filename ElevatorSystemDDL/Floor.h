#ifndef FLOOR_H
#define FLOOR_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Floor {
	
	int status, floor;

public:
	Floor();

	Floor(int, int);

	~Floor();

	int getFloor() const;
	int getStatus() const;

	void setFloor(int);
	void setStatus(int);
		 
};

bool compareFloor(Floor obj1, Floor obj2);

void sortVector(std::vector<Floor>&);

void fillFloorVector(std::vector<Floor>&);
void printFloorVector(const std::vector<Floor>&);
void addFloor(std::vector<Floor>&);
void eraseFloor(std::vector<Floor>&);
void eraseGroupFloor(std::vector<Floor>&);

#endif