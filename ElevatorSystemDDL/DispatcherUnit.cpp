#include "DispatcherUnit.h"
#include <string>
#include <iostream>
//definicja klasy DU

DispatcherUnit::DispatcherUnit(std::map <std::string, int> floorStatus_a) {
	floorStatus = floorStatus_a;
};

void DispatcherUnit::startElevatorSystem() {
	std::cout << floorStatus[0];
}