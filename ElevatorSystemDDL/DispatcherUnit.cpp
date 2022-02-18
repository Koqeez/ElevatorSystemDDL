#include "DispatcherUnit.h"
#include <iostream>
#include <map>

//definicja klasy DU

DispatcherUnit::DispatcherUnit(){};


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
	i= std::distance(floorStatus.begin(), floorStatus.end());
	std::cout << "Budynek sklada sie z "<< i <<" nastepujacych pieter. \n";
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
void DispatcherUnit::displayElevatorMap() {
	std::cout << allElevators.size();
};

void DispatcherUnit::eraseFloorMap() {
	if (floorStatus.empty()) {
		std::cout << "Mapa jest obecnie pusta. Nadus ENTER";
			return;
	}
	std::cout << "Mapa zostala usunieta. Nadus ENTER";
	floorStatus.clear();
}

void DispatcherUnit::addFloorMapElement() {
	//stworzenie metody umozliwiajacej wysylanie informacji o mapie
	
	int pietro = 0,poczatek = 0,koniec = 0,i = 0,status = 0;

	i = std::distance(floorStatus.begin(), floorStatus.end());
	poczatek = floorStatus.begin()->first;
	koniec = (poczatek + i)-1;

	//(std::prev(floorStatus.end())->first;

	std::cout << "Obecnie budynek ma wartosci od: " << poczatek << " , do:" << koniec << ", w sumie: " << i << " elementow."<<std::endl;
	std::cout << "Pietro musibyc dodane w zasiegu, n-1 do n+1" << std::endl;
	std::cout << "Podaj numer pietra ktore chcesz dodac : " << std::endl;
	std::cin >> pietro;
	if (pietro == poczatek - 1 || pietro == koniec + 1) {

		std::cout << "Podane pietro jest zgodne.\n Podaj status pietra: ";
		std::cin >> status;
		floorStatus.insert({ pietro,status });
		std::cout << "Element zostal dodany.";
		return;
	}
	std::cout << "Podane pietro jest niezgodne.\n";
	return;
}

void DispatcherUnit::eraseFloorMapElement() {
	int pietro = 0, poczatek = 0, koniec = 0, i = 0;

	i = std::distance(floorStatus.begin(), floorStatus.end());
	poczatek = floorStatus.begin()->first;
	koniec = (poczatek + i) - 1;

	std::cout << "Obecnie budynek ma wartosci od: " << poczatek << " , do:" << koniec << ", w sumie: " << i << " elementow." << std::endl;
	std::cout << "Pietro musibyc usuniete w zasiegu, n do n" << std::endl;
	std::cout << "Podaj numer pietra ktore chcesz usunac : " << std::endl;
	std::cin >> pietro;
	if (pietro == poczatek  || pietro == koniec ) {

		std::cout << "Podane pietro jest zgodne.\n";
		floorStatus.erase(pietro);
		std::cout << "Element zostal usuniety.";
		return;
	}
	std::cout << "Podane pietro jest niezgodne.\n";
	return;
}

void DispatcherUnit::eraseGroupFloorMap() {
	//dodanie sprawdzen integralnosciowych - inny mechanizm
	int pietro1 = 0, pietro2 = 0, poczatek = 0, koniec = 0, i = 0;

	i = std::distance(floorStatus.begin(), floorStatus.end());
	poczatek = floorStatus.begin()->first;
	koniec = (poczatek + i) - 1;

	std::cout << "Obecnie budynek ma wartosci od: " << poczatek << " , do:" << koniec << ", w sumie: " << i << " elementow." << std::endl;
	std::cout << "Pietra usuwane musza byc w zasiegu, n do n" << std::endl;
	std::cout << "Podaj numer pietra od ktorego chcesz usunac : " << std::endl;
	std::cin >> pietro1;
	std::cout << "Podaj numer pietra do ktorego chcesz usunac : " << std::endl;
	std::cin >> pietro2;
	for (std::map<int, int>::iterator itr = floorStatus.begin(); itr != floorStatus.end(); ++itr) {
		i = std::distance(floorStatus.begin(), itr);
		if (pietro1 <= i && pietro2 >= i) {
			floorStatus.erase(i);
		}
	}
}

void DispatcherUnit::addElevatorToMap(int number_a) {
	ElevatorCar temporary = ElevatorCar1.createElevator(number_a);
	allElevators.insert({ number_a,temporary});
}

void DispatcherUnit::addEnquiryToVector() {
	fillEnquiryVector(Enquiries);
}
void DispatcherUnit::displayEnquiries() {
	printVector(Enquiries);
}
void DispatcherUnit::addOneEnquiry() {
	addEnquiry(Enquiries);
}