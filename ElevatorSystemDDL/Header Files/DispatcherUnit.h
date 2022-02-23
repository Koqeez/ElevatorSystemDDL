#pragma once
#ifndef DISPATCHERUNIT_H
#define DISPATCHERUNIT_H
#include <vector>
#include <algorithm>
#include <thread>
#include "ElevatorCar.h"
#include "Floor.h"
#include "Algorytm.h"
#include "Windows.h"
#include "DataManagement.h"
#include "SimulationTime.h"

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



	ElevatorCar ElevatorCar1;
	Data Data1;
	SimulationTime* simulationTimePtr = new SimulationTime;
	
public:
	std::vector<Zapytanie>Enquiries;
	std::vector<Floor>floorStatus;
	std::vector<ElevatorCar> allElevators;
	std::vector<int> moveQueue;
	//startElevatorSystem() -- jedyna publiczna metoda pozwalaj�ca na wystartowanie programu

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
		//CZAS
			void incrementSimulationTime();
			void resetSimulationTime();
			int getTime();
			void runTimer();
		//TWORZENIE PODSTAW
			void createDefaultRequirements();
			void usePreconfiguratedSymulation();
		//RUCH WINDY
			void moveElevatorCarToManual();
			void goWithMoveQueue();
			void goWithMoveQueueX(int);
		//SYMULACJA
			void runSimulation();
			void resetSimulation();

	//ALGORYTMY
	void callCrossover();
	void callAlgorithmConfiguration();
	void simulationTest();
	void printMoveQueue();
	void printDNA();

	//DANE
	void callDane();

private:



	//stopSystem() -- odpowiada za wy��czenie programu

	//modu� EVENT(int floor) jako klasa dziedziczona


};
#endif