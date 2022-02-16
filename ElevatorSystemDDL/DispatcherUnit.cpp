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
		stopElevatorSystem();
		}
}
void DispatcherUnit::getRangeOfFloors() {
	//bez piêter poni¿ej zera
	std::cout << "Podaj pierwsze pietro:";
	std::cin >> minFloor;
	std::cout << "Podaj ostatnie pietro:";
	std::cin >> maxFloor;
	Floors = maxFloor - minFloor;
	std::cout << "Budynek bedzie mial " << Floors << " pieter.\n";
}
void DispatcherUnit::createFloorMap() {
	for (int i = 0; i < Floors; i++) {
		floorStatus.insert(std::make_pair(i, 0));
		
		//std::string Floor = "Floor";
		//floorStatus[Floor] = 0;
	}
}
void DispatcherUnit::displayFloorMap() {
	int i;
	std::cout << "Budynek sklada sie z nastepujacych pieter. \n";
	for (std::map<int, int>::iterator itr = floorStatus.begin(); itr != floorStatus.end(); ++itr) {

		if (itr == floorStatus.end()) {
			std::cout << "ERROR - BLAD ITERATORA\n";
		}
		i = std::distance(floorStatus.begin(), itr);
		
		if (i <= 9) {
			std::cout << "(Floor     " << (*itr).first << ") ma status: " << (*itr).second << "\n";
		}
		else if (i <= 99) {
			std::cout << "(Floor    " << (*itr).first << ") ma status: " << (*itr).second << "\n";
		}
		else if(i<=999){
			std::cout << "(Floor   " << (*itr).first << ") ma status: " << (*itr).second << "\n";
		}
		else {
			std::cout << "(Floor  " << (*itr).first << ") ma status: " << (*itr).second << "\n";
		}
	}
}

void DispatcherUnit::stopElevatorSystem() {
	std::cout << "Stoping elevator system.";
	exit(0);
}
void DispatcherUnit::eraseFloorMap() {
	if (floorStatus.empty()) {
		std::cout << "Mapa jest obecnie pusta. Nadus ENTER";
			return;
	}
	std::cout << "Mapa zostala usunieta. Nadus ENTER";
	floorStatus.clear();
}

void DispatcherUnit::addFloorMapElement() {
	int pietro = 0,poczatek = 0,koniec = 0,i = 0,status = 0;

	//i = std::distance(floorStatus.begin(), floorStatus.end());
	//poczatek = floorStatus.begin()->first;
	//koniec = floorStatus.end()->first;
	std::cout << "Obecnie budynek ma wartosci od: " << poczatek-1 << " , do:" << koniec+1 << ", w sumie: " << i << " elementow."<<std::endl;
	std::cout << "Pietro musibyc dodane w zasiegu, n-1 do n+1\n Podaj numer pietra ktore chcesz dodac:";
	std::cin >> pietro;
	if (pietro != poczatek - 2 || pietro != koniec + 2) {
		std::cout << "Podane pietro jest niezgodne.\n";
		return;
	}
	std::cout << "Podane pietro jest zgodne.\n Podaj status pietra: ";
	std::cin >> status;
	//floorStatus.insert({ pietro,status });
	std::cout << "Element zostal dodany. Nadus ENTER";

	
}