#include "DispatcherUnit.h"
#include <iostream>
#include <map>

//definicja klasy DU

DispatcherUnit::DispatcherUnit(){};

//w przypadku uzywania systemu z menu, wydaje sie mniej potrzebna
void DispatcherUnit::startElevatorSystem() {
	while (true) {
		getRangeOfFloors();
		createFloorMap();
		displayFloorMap();
		if (true) {
			stopElevatorSystem();
		}
	}
	
}
void DispatcherUnit::getRangeOfFloors() {
	//bez piêter poni¿ej zera
	std::cout << "Type first floor: ";
	std::cin >> minFloor;
	std::cout << "\nType last floor: ";
	std::cin >> maxFloor;
	Floors = maxFloor - minFloor;
	std::cout << "Building is " << Floors << " story tall.\n";
}
void DispatcherUnit::createFloorMap() {
	for (int i = 0; i < Floors; i++) {
		floorStatus.insert(std::make_pair(i, 0));
		
		//std::string Floor = "Floor";
		//floorStatus[Floor] = 0;
	}
}
void DispatcherUnit::displayFloorMap() {
	for (std::map<int, int>::iterator itr = floorStatus.begin(); itr != floorStatus.end(); ++itr) {
		std::cout <<"(Floor " << (*itr).first << ") ma status: " << (*itr).second << "\n";
	}
}

void DispatcherUnit::stopElevatorSystem() {
	std::cout << "Stoping elevator system.";
	exit(0);
}
void DispatcherUnit::eraseFloorMap() {
	floorStatus.clear();
}