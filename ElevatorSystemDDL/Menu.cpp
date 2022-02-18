#include "Menu.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <WinUser.h>
#include <stdio.h>

//----------------------------------------------------------------------------------
#include "Algorytm.h"

//-----------------------------------------------------------------------------------------


// cos
void ClearScreen()
{
	COORD cursorPosition;	
	cursorPosition.X = 0;	
	cursorPosition.Y = 0;	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void CursorAppear(bool visible) {
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = visible;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}



using namespace std;

void SetConsoleColour(WORD* Attributes, DWORD Colour)
{
	CONSOLE_SCREEN_BUFFER_INFO Info;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hStdout, &Info);
	*Attributes = Info.wAttributes;
	SetConsoleTextAttribute(hStdout, Colour);
}

void ResetConsoleColour(WORD Attributes)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Attributes);
}

Menu::Menu(string prompt_a, vector<string>& options_a) {
	Prompt = prompt_a;
	Options = options_a;
	SelectedIndex = 0;
};
Menu::Menu(){}; //domysly konstruktor jako obiekt inicjunijacy metode tworzaca menu

Menu::~Menu() {};


void Menu::DisplayOptions(){
	WORD Attributes = 0;
	//HANDLE Con;
	//Con = GetStdHandle(STD_OUTPUT_HANDLE);

	cout << Prompt;
	for (int i = 0; i < Options.size(); i++) {
		string currentOption = Options[i];
		string prefix;

		if (i == SelectedIndex) {
			prefix = "* ";
			SetConsoleColour(&Attributes, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE| BACKGROUND_GREEN);

		}
		else {
			prefix = "  ";
			//ResetConsoleColour(Attributes);
			SetConsoleColour(&Attributes, 7);
			

		}
		cout <<"\n"<<prefix << currentOption;
		
	}
	SetConsoleColour(&Attributes, 7);
	return;
}
int Menu::Run() {
	CursorAppear(false);
	do {
		ClearScreen();
		DisplayOptions();
		

		if (GetAsyncKeyState(VK_UP) & 1) {
			SelectedIndex--;
			if (SelectedIndex == -1) {
				SelectedIndex = Options.size() - 1;
			}
		}
		else if (GetAsyncKeyState(VK_DOWN) & 1) {
			SelectedIndex++;
			if (SelectedIndex == Options.size()) {
				SelectedIndex = 0;
			}
		}
		

	} while (GetAsyncKeyState(VK_RETURN) == 0);

	return SelectedIndex;
}

void Menu::RunMainMenu() {
	Sleep(1000);
	system("cls");
	string Prompt = "******************** MENU SYSTEM WINDY ********************";
	vector<string>Options = { "********** Opcje dotyczace - Mapy Pieter(Kontroler) **********","********** Opcje dotyczace - Wind **********","********** Opcje dotyczace - Algorytmu **********","********** Wywsietl informacje **********" ,"********** Wyjscie **********" };
	Menu mainMenu(Prompt, Options);
	int selectedIndex = mainMenu.Run();

	switch (selectedIndex) {
	case 0:
		Sleep(1000);
		system("CLS");
		DisplayMapOptions();
		break;
	case 1:
		Sleep(1000);
		system("CLS");
		DisplayElevatorOptions();
		break;
	case 2:
		Sleep(1000);
		system("CLS");
		DisplayAlgorithmOptions();
		break;
	case 3:
		DisplayInformation();
		break;
	case 4:
		ExitMenu();
		break;
	case 5:
		break;
	}
}

void Menu::DisplayMapOptions() {
	Sleep(1000);
	system("cls");
	string Prompt = "******************** MENU DOTYCZACE MAPY PIETER ********************";
	vector<string>Options = {"********** Dodaj Mape **********","********** Zmien mape **********", "********** Usun mape **********", "********** Wyswietl mape **********","********** POWROT **********"};
	Menu MapMenu(Prompt, Options);
	
	int SelectedIndex = MapMenu.Run();

	switch (SelectedIndex) {
	case 0:
		system("cls");
		DispatcherUnit1.getRangeOfFloors();
		DispatcherUnit1.createFloorMap();
		MenuMapDisplacer();
		break;
	case 1:
		Sleep(2000);
		DisplayMapChangeOptions();
		break;
	case 2:
		system("cls");
		DispatcherUnit1.eraseFloorMap();
		MenuMapDisplacer();
		break;
	case 3:
		system("cls");
		DispatcherUnit1.displayFloorMap();
		MenuMapDisplacer();
		break;
	case 4:
		system("cls");
		RunMainMenu();
		//MenuDisplacer();
	}
}

void Menu::DisplayElevatorOptions() {
	Sleep(1000);
	system("cls");
	int number_a;
	string Prompt = "******************** MENU DOTYCZACE WIND ********************";
	vector<string>Options = { "********** Dodaj Winde **********","********** Wywsietl mape wind **********", "********** Usun mape **********","********** POWROT **********" };
	Menu ElevatorMenu(Prompt, Options);

	int SelectedIndex = ElevatorMenu.Run();

	switch (SelectedIndex) {
	case 0:
		system("cls");
		std::cout << "Wpisz numer windy: " << std::endl;
		std::cin >> number_a;
		DispatcherUnit1.addElevatorToMap(number_a);
		MenuElevatorDisplacer();
		break;
	case 1:
		system("CLS");
		Sleep(2000);
		DispatcherUnit1.displayElevatorMap();
		MenuElevatorDisplacer();
		break;
	case 2:
		system("cls");
		DispatcherUnit1.eraseFloorMap();
		MenuMapDisplacer();
		break;
	case 3:
		system("cls");
		DispatcherUnit1.displayFloorMap();
		MenuMapDisplacer();
		break;
	case 4:
		system("cls");
		RunMainMenu();
		//MenuDisplacer();
	}
}

void Menu::DisplayAlgorithmOptions() {
	Sleep(1000);
	system("cls");
	string Prompt = "******************** MENU DOTYCZACE ALGORYTMU ********************";
	vector<string>Options = { "********** ZOBACZ CROSSOVER **********","********** POWROT **********" };
	Menu AlgorithmMenu(Prompt, Options);

	int SelectedIndex = AlgorithmMenu.Run();

	switch (SelectedIndex) {
	case 0:
		system("cls");
		CrossoverView();
		MenuAlgorithmDisplacer();
		break;
	case 1:
		system("cls");
		RunMainMenu();
		break;
	}
}

void Menu::DisplayMapChangeOptions() {
	Sleep(1000);
	system("cls");
	string Prompt = "******************** MENU DOTYCZACE ZMIANY MAPY ********************";
	vector<string>Options = { "********** DODAJ ELEMENT **********","********** USUN ELEMENT **********", "********** USUN GRUPE ELEMENTOW **********","********** POWROT **********" };
	Menu MapChangeMenu(Prompt, Options);

	int SelectedIndex = MapChangeMenu.Run();

	switch (SelectedIndex) {
	case 0:
		Sleep(2000);
		system("cls");
		DispatcherUnit1.addFloorMapElement();
		MenuMapChangeDisplacer();
		break;
	case 1:
		Sleep(2000);
		system("cls");
		DispatcherUnit1.eraseFloorMapElement();
		MenuMapChangeDisplacer();
		break;
	case 2:
		Sleep(2000);
		system("cls");
		DispatcherUnit1.eraseGroupFloorMap();
		MenuMapChangeDisplacer();
		break;
	case 3:
		system("cls");
		DisplayMapOptions();
		break;
	case 4:
		//system("cls");
		//DisplayMapOptions();
		//MenuDisplacer();
		break;
	}
}






void Menu::DisplayInformation() {
	system("cls");
	cout << "Informacje.";
	cout << "\nNadus enter by wrocic do menu glownego.";
	MenuDisplacer();
	
}


void Menu::ExitMenu() {
	system("cls");
	cout << "WYJSCIE";
	exit(0);
}

//zmienic to na osobna, jedna metode z parametrami
void Menu::MenuDisplacer() {
	Sleep(1000);
	bool flaga = true;
	while (flaga) {
		if (GetAsyncKeyState(VK_RETURN)) {
			flaga = false;
			system("cls");
			RunMainMenu();
		}
	}
}
void Menu::MenuMapDisplacer() {
	Sleep(1000);
	bool flaga = true;
	while (flaga) {
		if (GetAsyncKeyState(VK_RETURN)) {
			flaga = false;
			system("cls");
			DisplayMapOptions();
		}
	}
}

void Menu::MenuElevatorDisplacer() {
	Sleep(1000);
	bool flaga = true;
	while (flaga) {
		if (GetAsyncKeyState(VK_RETURN)) {
			flaga = false;
			system("cls");
			DisplayElevatorOptions();
		}
	}
}
void Menu::MenuAlgorithmDisplacer() {
	Sleep(1000);
	bool flaga = true;
	while (flaga) {
		if (GetAsyncKeyState(VK_RETURN)) {
			flaga = false;
			system("cls");
			DisplayAlgorithmOptions();
		}
	}
}

void Menu::MenuMapChangeDisplacer() {
	Sleep(1000);
	bool flaga = true;
	while (flaga) {
		if (GetAsyncKeyState(VK_RETURN)) {
			flaga = false;
			system("cls");
			DisplayMapChangeOptions();
		}
	}
}



/*
do {
		cout << i;
		i++;
	} while(GetAsyncKeyState(VK_RETURN)!= 1);
	int i = 0;
	while (1) {
		if(GetAsyncKeyState(VK_DOWN) & 1){
				cout << i << "\n";
				i++;
		}
	}
	*/