#pragma once
#ifndef DISPATCHERUNIT_H
#define DISPATCHERUNIT_H
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include "ElevatorCar.h"
#include "Zapytania.h"
#include "Floor.h"
#include "Algorytm.h"

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
	std::vector<Floor>floorStatus; 
	std::vector<ElevatorCar> allElevators; 
	std::vector<int> moveQueue;



	ElevatorCar ElevatorCar1;




public:
	//startElevatorSystem() -- jedyna publiczna metoda pozwalaj¹ca na wystartowanie programu

	DispatcherUnit();


	//PIETRA
	void createFloorVector();
	void displayFloorVector();
	void sortFloorVector();
	void eraseFloorVector();
	void addFloorVectorElement();
	void eraseFloorVectorElement();
	void eraseGroupFloorVector();

	//WINDY
	void addElevatorToVector();
	void displayElevatorVector();
	void clearElevatorVector();

	//ZAPYTANIA
	void addEnquiryToVector();
	void displayEnquiries();
	void addOneEnquiry();
	void eraseOneEnquiryDisplay();

	//SYMULACJA
	void createDefaultRequirements();
	void moveElevatorCarToManual();
	void goWithMoveQueue();

	//ALGORYTMY
	void callCrossover();
	void callTest();
	void printMoveQueue();

private:



	//stopSystem() -- odpowiada za wy³¹czenie programu

	//modu³ EVENT(int floor) jako klasa dziedziczona


};
#endif