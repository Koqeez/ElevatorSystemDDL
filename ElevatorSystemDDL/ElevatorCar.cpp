#include "ElevatorCar.h"

//definicja klasy EC
ElevatorCar::ElevatorCar() {};

ElevatorCar::ElevatorCar(int number_a, int capacity_a, int currentFloor_a, ElevatorCarDirection ElevatorCarDirection_a) {
	if (capacity_a <= 0) return;
	capacity = capacity_a;
	currentFloor = currentFloor_a;
	direction = ElevatorCarDirection_a;
	number = number_a;
};
ElevatorCar::~ElevatorCar() {};


ElevatorCar ElevatorCar::createElevator(int number_a,int capacity_a) {
	ElevatorCar ElevatorObj(number_a,capacity_a,0,IDLE);
	return ElevatorObj;
}
int ElevatorCar::getCapacity(){
	return capacity;
}
int ElevatorCar::getCurrentFloor(){
	return currentFloor;
}
int ElevatorCar::getNumber(){
	return number;
}
ElevatorCar::ElevatorCarDirection ElevatorCar::getDirection(){
	return direction;
}

void ElevatorCar::moveToFloor(int floor_a) {
}