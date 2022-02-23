#pragma once
#ifndef ELEVATOR_H
#define ELEVATOR_H
#include <string>
#include "Floor.h"

class ElevatorCar {

	//bool isMoving;
	//bool isMovingUp;


	int capacity = 0, currentFloor = 0, currentLoad = 0, number = 0;
	int minFloorElev, maxFloorElev;
	//int destination
	enum ElevatorCarDirection {DOWN ,UP, IDLE};
	const char* enum_str[3] = { "DOWN", "UP", "IDLE"};


	ElevatorCarDirection direction = IDLE;
	//IDLE (->) minFloor

	// W przysz³oœci mo¿e byæ podzielone na segmenty
	//currentFloor
	//startFloor
	//endFloor

public:
	ElevatorCar();
	ElevatorCar(int number_a, int capacity_a, int currentFloor_a,int minFloorElev_a,int maxFloorElev_a, ElevatorCarDirection ElevatorCarDirection_a);
	~ElevatorCar();
	ElevatorCar createElevator(int number_a, int capacity_a);
	void moveToFloor(int);

	int getCapacity();
	int getCurrentFloor();
	int getNumber();
	int getMinFloorElev();
	int getMaxFloorElev();

	void setDirection(int);
	ElevatorCarDirection getDirection();
	const char* getDirectionString();


};
#endif