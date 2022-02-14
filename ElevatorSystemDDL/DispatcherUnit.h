#pragma once
#include <list>
#include <vector>
#include <map>

//modu³ odpowiadaj¹cy za optymalne funkcjonowanie windy
class DispatcherUnit {
	//How to move the elevator car
	//List<Elevator> allElevators -- w przypadku wiêkszej iloœci wind
	//List<Floors> allFloors -- struktura odpowiadaj¹ca za po³o¿enie piêter

	//std::list<int> allFloors;
	//std::vector<int> requests;

	std::map<int, int> floorStatus;
	int minFloor, maxFloor, Floors;



	

public:
	//startElevatorSystem() -- jedyna publiczna metoda pozwalaj¹ca na wystartowanie programu
	
	DispatcherUnit();

	void startElevatorSystem();
private:
	void getRangeOfFloors();



	void createFloorMap();
	void displayFloorMap();

	void stopElevatorSystem();
	

	//stopSystem() -- odpowiada za wy³¹czenie programu

	//modu³ EVENT(int floor) jako klasa dziedziczona


};