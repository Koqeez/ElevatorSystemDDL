#pragma once
#include <list>
#include <vector>
#include <map>
#include "ElevatorCar.h"

//modu� odpowiadaj�cy za optymalne funkcjonowanie windy
class DispatcherUnit {
	//How to move the elevator car

	//Kryteria
	//
	//Transported ilosc
	//ElapsedTime sekundy
	//Transported/s ilosc.00
	//AvgWaitingTime sekundy.00
	//MaxMovingTime sekundy.00
	//Moves[vectors] ilosc
 
	
	//List<Elevator> allElevators -- w przypadku wi�kszej ilo�ci wind
	

	//Pierwsza ma wy��cznie mo�liwo�� tworzenia zapytania w g�r�, d�ugo��-1 ma mo�liwo�� wykonania zapytania jedynie w d� 
	//
	// 
	//List<Floors> allFloors -- struktura odpowiadaj�ca za po�o�enie pi�ter

	//std::list<int> allFloors;
	// 
	// 
	//std::vector<int> requests;
	

	std::map<int, int> floorStatus; //mapa pieter
	std::map<int, ElevatorCar> allElevators; //mapa wind



	int minFloor, maxFloor, Floors;

	ElevatorCar ElevatorCar1;


	

public:
	//startElevatorSystem() -- jedyna publiczna metoda pozwalaj�ca na wystartowanie programu
	
	DispatcherUnit();

	void startElevatorSystem();


	//w przypadku zastosowania systemu bez menu funkcje te powinny by� private
	void getRangeOfFloors();

	//tworzenie i wyswietlanie mapy
	void createFloorMap();
	void displayFloorMap();
	void displayElevatorMap();

	//usuwanie mapy
	void eraseFloorMap();

	//zmiana mapy
	void addFloorMapElement();
	void eraseFloorMapElement();
	void eraseGroupFloorMap();


	void addElevatorToMap(int number_a);

	void stopElevatorSystem();
private:

	

	//stopSystem() -- odpowiada za wy��czenie programu

	//modu� EVENT(int floor) jako klasa dziedziczona


};