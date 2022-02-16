#include <iostream>
#include "ElevatorCar.h"
#include "DispatcherUnit.h"
#include <conio.h>
using namespace std;
//display jako funkcja wywo³uj¹ca program

void menu(int& c);

int main() {
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
	return 0;
}

void menu(int& c) {
	//caly system trzyma sie do miejsca w ktorym nie ma rozgalenzien. zamiast 3 opcji, 1.1, 1.2, 1.3
	system("cls");
	cout << "\n***** MENU *****\n";
	cout << "\nWybierz opcje \n";
	//mapy
	cout << "\n1. Dodaj mape\n";
	cout << "\n2. Zmien mape\n"; //nie impelementuje, brak rozgalenzienia na zmien ->(dodaj,usun,zmien wartoœæ) elementu(grupy elementow)
	cout << "\n3. Usun mape\n";
	cout << "\n4. Wyswietl mape\n";

	//stworzenie zapytania jako status pietra


	//informacje dotyczace windy


	cout << "\n5. Zamknij program\n";
	cin >> c;
}