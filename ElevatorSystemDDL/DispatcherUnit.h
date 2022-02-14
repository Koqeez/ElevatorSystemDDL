#pragma once
#include <list>
#include <vector>
#include <map>
#include <string>

//modu� odpowiadaj�cy za optymalne funkcjonowanie windy
class DispatcherUnit {
	//How to move the elevator car
	//List<Elevator> allElevators -- w przypadku wi�kszej ilo�ci wind
	//List<Floors> allFloors -- struktura odpowiadaj�ca za po�o�enie pi�ter

	//std::list<int> allFloors;
	//std::vector<int> requests;

	std::map<std::string, int> floorStatus;



	

public:
	//startElevatorSystem() -- jedyna publiczna metoda pozwalaj�ca na wystartowanie programu
	
	DispatcherUnit(std::map<std::string,int> floorStatus_a);

	void startElevatorSystem();
private:
	void createFloorMap();

	//stopSystem() -- odpowiada za wy��czenie programu

	//modu� EVENT(int floor) jako klasa dziedziczona


};