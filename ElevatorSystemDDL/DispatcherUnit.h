#pragma once
#include <list>
#include <vector>
#include <map>
#include "ElevatorCar.h"
#include "Zapytania.h"
#include "Floor.h"


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
 
		

	//Pierwsza ma wy³¹cznie mo¿liwoœæ tworzenia zapytania w górê, d³ugoœæ-1 ma mo¿liwoœæ wykonania zapytania jedynie w dó³ 

	//std::vector<int> requests;
	
	std::vector<Zapytanie>Enquiries;
	std::vector<Floor>floorStatus; //mapa pieter
	std::vector<ElevatorCar> allElevators; //mapa wind



	ElevatorCar ElevatorCar1;


	

public:
	//startElevatorSystem() -- jedyna publiczna metoda pozwalaj¹ca na wystartowanie programu
	
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

	

	//stopSystem() -- odpowiada za wy³¹czenie programu

	//modu³ EVENT(int floor) jako klasa dziedziczona


};