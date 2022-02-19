#pragma once
#include <list>
#include <vector>
#include <map>
#include "ElevatorCar.h"
#include "Zapytania.h"
#include "Floor.h"


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
 
		

	//Pierwsza ma wy��cznie mo�liwo�� tworzenia zapytania w g�r�, d�ugo��-1 ma mo�liwo�� wykonania zapytania jedynie w d� 

	//std::vector<int> requests;
	
	std::vector<Zapytanie>Enquiries;
	std::vector<Floor>floorStatus; //mapa pieter
	std::vector<ElevatorCar> allElevators; //mapa wind



	ElevatorCar ElevatorCar1;


	

public:
	//startElevatorSystem() -- jedyna publiczna metoda pozwalaj�ca na wystartowanie programu
	
	DispatcherUnit();




	//tworzenie i wyswietlanie mapy
	void createFloorVector();
	void displayFloorVector();
	void sortFloorVector();
	//usuwanie mapy
	void eraseFloorVector();
	//zmiana mapy
	void addFloorVectorElement();
	void eraseFloorVectorElement();
	void eraseGroupFloorVector();


	void addElevatorToMap();
	void displayElevatorMap();
	void clearElevatorMap();

	void addEnquiryToVector();
	void displayEnquiries();
	void addOneEnquiry();

private:

	

	//stopSystem() -- odpowiada za wy��czenie programu

	//modu� EVENT(int floor) jako klasa dziedziczona


};