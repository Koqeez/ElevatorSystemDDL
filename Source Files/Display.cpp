#include <iostream>
#include "ElevatorCar.h"
#include "DispatcherUnit.h"
#include "Menu.h"
#include "PlatformUtils.h"

//display jako funkcja wywołująca program
int main() {
	Menu menu;
	menu.RunMainMenu();
	return 0;
}

// Remove or properly terminate the old menu code