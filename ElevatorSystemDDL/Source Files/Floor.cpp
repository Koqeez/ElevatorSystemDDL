#include "Floor.h"
#include "GlobalVariables.h"

int maxFloor;
int minFloor;
int Floors;
int GlobalID = 0;

Floor::Floor() {
	/*int floor, status;
	std::cout << "Wpisz pietro: " << std::endl;
	std::cin >> floor;
	std::cout << "Wpisz status pietra: " << std::endl;
	std::cin >> status;
	while (x == y) {
		cout << "Miejsce docelowe nie moze byc takie samo jak poczatkowe" << endl << "Wpisz miejsce docelowe: " << endl;
		cin >> y;
	}
	MiejsceP = x;
	MiejsceD = y;
	ID = GlobalID;
	GlobalID++;
	*/
}
Floor::Floor(int floor_a, int status_a) {
	floor = floor_a;
	status = status_a;
}
Floor::~Floor() {};

int Floor::getFloor() const {
	return floor;

}
int Floor::getStatus() const {
	return status;
}

void Floor::setFloor(int floor_a) {
	floor = floor_a;
}
void Floor::setStatus(int status_a) {
	status = status_a;
}

bool compareFloor(Floor obj1, Floor obj2) {

	return (obj1.getFloor() < obj2.getFloor());
}

void sortVector(std::vector<Floor>& newFloorVector) {
	std::cout << "Przed posortowaniem: " << std::endl;
	printFloorVector(newFloorVector);
	std::sort(newFloorVector.begin(), newFloorVector.end(), compareFloor);
	std::cout << "Po posortowaniu: " << std::endl;
	printFloorVector(newFloorVector);
	return;
}

void fillFloorVector(std::vector<Floor>& newFloorVector) {
	//bez piêter poni¿ej zera
	if (newFloorVector.empty()) {
		do {
			if (std::cin.fail()) {
				std::cin.ignore(INT_MAX, '\n');
				std::cin.clear();
			}
			if (std::cin.peek() == '\n') std::cin.ignore();
			std::cout << "Podaj pierwsze pietro:";
			std::cin >> ::minFloor;
		} while (std::cin.fail());
		std::cout << "Podaj ostatnie pietro:";
		std::cin >> ::maxFloor;
		if (::minFloor > ::maxFloor) {
			std::cout << "Podane dane sa zle." << std::endl;
			return;
		}
		::Floors = ::maxFloor - ::minFloor;
		::maxFloor--;
		std::cout << "Budynek bedzie mial " << ::Floors << " pieter.\n";

		for (int i = 0; i < ::Floors; i++) {
			Floor Floor(i, 0);
			newFloorVector.push_back(Floor);
		}
	}
	else {
		std::cout << "Budynek ma juz stworzone pietra. Przed stworzeniem nowego, usun stary." << std::endl;
	}
}

void fillFloorVectorXY(std::vector<Floor>& newFloorVector, int X, int Y){
	//X - minFloor Y - maxFloor
	::Floors = Y - X;
	Y--;
	for (int i = 0; i < ::Floors; i++) {
		Floor Floor(i, 0);
		newFloorVector.push_back(Floor);
	}
	::maxFloor = Y;
	::minFloor = X;
}

void printFloorVariables() {
	std::cout << "Pietro minimalne: " <<minFloor<<", pietro maksymalne: "<<maxFloor<<", ilosc pieter: "<<Floors<< std::endl;
}

void printFloorVector(const std::vector<Floor>& newFloorVector) {
	unsigned int size = newFloorVector.size();
	if (size == 0) {
		std::cout << "Brak pieter, budynek jeszcze nie powstal." << std::endl;
		return;
	}
	std::cout << "Budynek sklada sie z " << size << " nastepujacych pieter." << std::endl;
	for (unsigned int i = 0; i < size; i++) {
		if (i <= 9) {
			std::cout << "Pietro nr:    " << newFloorVector[i].getFloor() << " , o statusie: " << newFloorVector[i].getStatus() << std::endl;
		}
		else if (i <= 99) {
			std::cout << "Pietro nr:   " << newFloorVector[i].getFloor() << " , o statusie: " << newFloorVector[i].getStatus() << std::endl;
		}
		else if (i <= 999) {
			std::cout << "Pietro nr:  " << newFloorVector[i].getFloor() << " , o statusie: " << newFloorVector[i].getStatus() << std::endl;
		}
		else {
			std::cout << "Pietro nr: " << newFloorVector[i].getFloor() << " , o statusie: " << newFloorVector[i].getStatus() << std::endl;
		}
	}
}


void addFloor(std::vector<Floor>& newFloorVector) {
	int pietro, poczatek, koniec, status;

	poczatek = 0;
	koniec = newFloorVector.size();


	std::cout << "Obecnie budynek ma wartosci od: " << poczatek << " , do:" << koniec-1 << ", w sumie: " << koniec << " elementow." << std::endl;
	std::cout << "Pietro musibyc dodane w zasiegu, n(0)-1 do n(n)+1" << std::endl;
	std::cout << "Podaj numer pietra ktore chcesz dodac : " << std::endl;
	std::cin >> pietro;
	if (pietro == poczatek - 1 || pietro == koniec) {

		std::cout << "Podane pietro jest zgodne.\n Podaj status pietra: ";
		std::cin >> status;
		Floor Floor(pietro, status);
		newFloorVector.push_back(Floor);
		std::cout << "Element zostal dodany.";
		return;
	}
	std::cout << "Podane pietro jest niezgodne.\n";
	return;
}
void eraseFloor(std::vector<Floor>& newFloorVector) {


	int pietro, poczatek, koniec;

	
	poczatek = 0;
	koniec = newFloorVector.size();

	std::cout << "Obecnie budynek ma wartosci od: " << poczatek << " , do:" << koniec << ", w sumie: " << koniec << " elementow." << std::endl;
	std::cout << "Pietro musibyc usuniete w zasiegu, n(0) lub n(n)" << std::endl;
	std::cout << "Podaj numer pietra ktore chcesz usunac : " << std::endl;
	std::cin >> pietro;
	if (pietro == poczatek || pietro == koniec-1) {

		std::cout << "Podane pietro jest zgodne.\n";
		newFloorVector.erase(newFloorVector.begin() + pietro);
		std::cout << "Element zostal usuniety.";
		return;
	}
	std::cout << "Podane pietro jest niezgodne.\n";
	return;
}
void eraseGroupFloor(std::vector<Floor>& newFloorVector) {
	

	int pietro1 ,pietro2 , poczatek, koniec;


	poczatek = 0;
	koniec = newFloorVector.size();


	std::cout << "Obecnie budynek ma wartosci od: " << poczatek << " , do:" << koniec << ", w sumie: " << koniec << " elementow." << std::endl;
	std::cout << "Pietra usuwane musza byc w zasiegu, n do n" << std::endl;
	std::cout << "Podaj numer pietra od ktorego chcesz usunac : " << std::endl;
	std::cin >> pietro1;
	std::cout << "Podaj numer pietra do ktorego chcesz usunac : " << std::endl;
	std::cin >> pietro2;
	//sprawdzanie integralnosciowe - ostatnie pietro czy jest w zakresie i nie jest takie jak 1, masa bugow
	newFloorVector.erase(newFloorVector.begin() + pietro1 - 1, newFloorVector.begin() + pietro2 - 1);
	std::cout<<" Elementy zostaly usunienete. ";	
	return;
}
bool floorZeroCheck(int& floor_a) {
	if (floor_a == 0) {
		std::cout << "Ilosc pieter jest zerowa." << std::endl;
		return true;
	}
	return false;

}