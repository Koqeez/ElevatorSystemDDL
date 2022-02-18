#pragma once
#include <list>
#include <vector>
#include <map>
#include "ElevatorCar.h"

//modu³ odpowiadaj¹cy za optymalne funkcjonowanie windy
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
 
	
	//List<Elevator> allElevators -- w przypadku wiêkszej iloœci wind
	

	//Pierwsza ma wy³¹cznie mo¿liwoœæ tworzenia zapytania w górê, d³ugoœæ-1 ma mo¿liwoœæ wykonania zapytania jedynie w dó³ 
	//
	// 
	//List<Floors> allFloors -- struktura odpowiadaj¹ca za po³o¿enie piêter

	//std::list<int> allFloors;
	// 
	// 
	//std::vector<int> requests;
	

	std::map<int, int> floorStatus; //mapa pieter
	std::map<int, ElevatorCar> allElevators; //mapa wind



	int minFloor, maxFloor, Floors;

	ElevatorCar ElevatorCar1;


	

public:
	//startElevatorSystem() -- jedyna publiczna metoda pozwalaj¹ca na wystartowanie programu
	
	DispatcherUnit();

	void startElevatorSystem();


	//w przypadku zastosowania systemu bez menu funkcje te powinny byæ private
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

	

	//stopSystem() -- odpowiada za wy³¹czenie programu

	//modu³ EVENT(int floor) jako klasa dziedziczona


};