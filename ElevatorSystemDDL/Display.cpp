#include <iostream>
#include "ElevatorCar.h"
#include "DispatcherUnit.h"
#include "Menu.h"
#include <conio.h>


//display jako funkcja wywo³uj¹ca program
int main() {

	Menu Menu;
	Menu.RunMainMenu();

	return 0;
}


/*

void menu(int& c);
STARE MENU
void menu(int& c) {
	//caly system trzyma sie do miejsca w ktorym nie ma rozgalenzien. zamiast 3 opcji, 1.1, 1.2, 1.3
	system("cls");
	std::cout << "\n***** MENU *****\n";
	std::cout << "\nWybierz opcje \n";
	//mapy
	std::cout << "\n1. Dodaj mape\n";
	std::cout << "\n2. Zmien mape\n"; //nie impelementuje, brak rozgalenzienia na zmien ->(dodaj,usun,zmien wartoœæ) elementu(grupy elementow)
	std::cout << "\n3. Usun mape\n";
	std::cout << "\n4. Wyswietl mape\n";

	//stworzenie zapytania jako status pietra


	//informacje dotyczace windy


	std::cout << "\n5. Zamknij program\n";
	std::cin >> c;
}

//program wyœwietlaj¹cy menu
	//mo¿liwoœæ zmieniania mapy(odzwierciedlenie systemu piêter) ->zmiana, dodawanie, usuwanie;
	//wyœwietlanie mapy

	int choice{ 0 };


	system("cls");

	DispatcherUnit Display1;

	do {
		menu(choice);

		switch (choice) {
			case 1://dodaj mape
				Display1.getRangeOfFloors();
				Display1.createFloorMap();
				cout << "\nZrobione - nadus ENTER\n";
				_getch();
				break;
			case 2://zmien mape
				break;
			case 3://usun mape
				//je¿eli mapa nie jest ju¿ pusta
				Display1.eraseFloorMap();
				cout << "\nZrobione - nadus ENTER\n";
				_getch();
				break;
			case 4://wyswietl mape
				Display1.displayFloorMap();
				cout << "\nZrobione - nadus ENTER\n";
				_getch();
				break;
			case 5:
				Display1.stopElevatorSystem();
		}

	} while (1);

	//Display1.startElevatorSystem();
*/