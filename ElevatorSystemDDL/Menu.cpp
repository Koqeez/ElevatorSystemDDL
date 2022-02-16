#include "Menu.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <WinUser.h>
#include <stdio.h>

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
	string Prompt = "Menu";
	vector<string>Options = { "<<Opcja 1 >>","<<Opcja 2 >>","<<Opcja 3 >>" };
	Menu mainMenu(Prompt, Options);
	int selectedIndex = mainMenu.Run();
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