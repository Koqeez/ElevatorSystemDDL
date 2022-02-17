#pragma once
#include <string>

class ElevatorCar {
	bool isMoving;
	bool isMovingUp;


	int capacity ,destination ,currentFloor ,currentLoad ,number;

	enum ElevatorCarDirection {
		UP,DOWN,IDLE
	};
	ElevatorCarDirection direction;
	//IDLE (->) minFloor
	
	// W przysz³oœci mo¿e byæ podzielone na segmenty
	//currentFloor
	//startFloor
	//endFloor

public:
	ElevatorCar();
	ElevatorCar(int number_a ,int capacity_a, int currentFloor_a = 0, ElevatorCarDirection ElevatorCarDirection_a = IDLE);
	~ElevatorCar();
	ElevatorCar createElevator(int number_a);
	void moveToFloor(int floor_a);





};