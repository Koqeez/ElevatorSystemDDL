#include "ElevatorCar.h"
#include "GlobalVariables.h"

//definicja klasy EC
ElevatorCar::ElevatorCar() {};

ElevatorCar::ElevatorCar(int number_a, int capacity_a, int currentFloor_a, int minFloorElev_a, int maxFloorElev_a, ElevatorCarDirection ElevatorCarDirection_a) {
	if (capacity_a <= 0) return;
	capacity = capacity_a;
	currentFloor = currentFloor_a;
	direction = ElevatorCarDirection_a;
	number = number_a;
	minFloorElev = minFloorElev_a;
	maxFloorElev = maxFloorElev_a;
};
ElevatorCar::~ElevatorCar() {};


ElevatorCar ElevatorCar::createElevator(int number_a, int capacity_a) {
	ElevatorCar ElevatorObj(number_a, capacity_a, 0, minFloor, maxFloor, IDLE);
	return ElevatorObj;
}
int ElevatorCar::getCapacity() {
	return capacity;
}
int ElevatorCar::getCurrentFloor() {
	return currentFloor;
}
int ElevatorCar::getNumber() {
	return number;
}
ElevatorCar::ElevatorCarDirection ElevatorCar::getDirection() {
	return direction;
}
int ElevatorCar::getMaxFloorElev() {
	return maxFloorElev;
}
int ElevatorCar::getMinFloorElev() {
	return minFloorElev;
}

void ElevatorCar::setDirection(int direction) {
	if (direction == 0) {
		this->direction = DOWN;
	}
	else if (direction) {
		this->direction = UP;
	}
	else {
		this->direction = IDLE;
	}
}

const char* ElevatorCar::getDirectionString() {
	int directionENUM;
	directionENUM = this->getDirection();
	return enum_str[direction];
}

void ElevatorCar::moveToFloor(int floor_a) {
	currentFloor = floor_a;
}