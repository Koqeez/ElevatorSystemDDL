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


ElevatorCar ElevatorCar::createElevator(int number_a) {
	ElevatorCar Elevator(number_a, 5, 0);
	return Elevator;
}
void ElevatorCar::moveToFloor(int floor_a) {

}