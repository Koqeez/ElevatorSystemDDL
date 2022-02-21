#pragma once
#ifndef ELEVATOR_H
#define ELEVATOR_H
#include <string>

class ElevatorCar {

	//bool isMoving;
	//bool isMovingUp;


	int capacity = 0, currentFloor = 0, currentLoad = 0, number = 0;

	//int destination
	enum ElevatorCarDirection {
		UP, DOWN, IDLE
	};
	ElevatorCar::ElevatorCarDirection direction = IDLE;
	//IDLE (->) minFloor

	// W przysz³oœci mo¿e byæ podzielone na segmenty
	//currentFloor
	//startFloor
	//endFloor

public:
	ElevatorCar();
	ElevatorCar(int number_a, int capacity_a, int currentFloor_a, ElevatorCarDirection ElevatorCarDirection_a);
	~ElevatorCar();
	ElevatorCar createElevator(int number_a, int capacity_a);
	void moveToFloor(int);

	int getCapacity();
	int getCurrentFloor();
	int getNumber();
	ElevatorCarDirection getDirection();


};
#endif