#include "../Header Files/Menu.h"
#include "../Header Files/PlatformUtils.h"
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>

// Cross-platform console color definitions
#ifdef _WIN32
    #define BACKGROUND_WHITE (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE)
#else
    #define RESET_COLOR "\033[0m"
    #define WHITE_BG "\033[47m"
    #define BLACK_TEXT "\033[30m"
#endif

// Cross-platform console functions
void SetConsoleColour(WORD* Attributes, DWORD Colour) {
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO Info;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hStdout, &Info);
    *Attributes = Info.wAttributes;
    SetConsoleTextAttribute(hStdout, Colour);
#else
    (void)Attributes; // Avoid unused parameter warning
    (void)Colour;
    std::cout << WHITE_BG << BLACK_TEXT;
#endif
}

void ResetConsoleColour(WORD Attributes) {
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Attributes);
#else
    (void)Attributes; // Avoid unused parameter warning
    std::cout << RESET_COLOR;
#endif
}

// Cross-platform key detection
bool IsReturnKeyPressed() {
#ifdef _WIN32
    char ch = _getch();
    return ch == '\r';
#else
    char ch = _getch();
    return ch == '\n';
#endif
}

//----------------------------------------------------------------------------------
#include "Algorytm.h"
//----------------------------------------------------------------------------------

void Menu::ClearScreen() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

char Menu::GetKeyPress() {
#ifdef _WIN32
	return _getch();
#else
	struct termios oldattr, newattr;
	char ch;
	tcgetattr(STDIN_FILENO, &oldattr);
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
	return ch;
#endif
}

using namespace std;

Menu::Menu(string prompt_a, vector<string>& options_a) {
	Prompt = prompt_a;
	Options = options_a;
	SelectedIndex = 0;
};

Menu::Menu(){}; //domysly konstruktor jako obiekt inicjunijacy metode tworzaca menu
Menu::~Menu() {};

void Menu::PrintMenu(int selectedIndex) {
    ClearScreen();
    std::cout << Prompt << std::endl;
    
    for (size_t i = 0; i < Options.size(); ++i) {
        if (i == static_cast<size_t>(selectedIndex)) {
            // Your highlighting code...
        }
        std::cout << Options[i] << std::endl;
    }
}

void Menu::DisplayOptions() {
    for (size_t i = 0; i < Options.size(); i++) {
        if (i == static_cast<size_t>(SelectedIndex)) {
            SetConsoleColor(true);  // Highlight selected option
        }
        std::cout << Options[i] << std::endl;
        if (i == static_cast<size_t>(SelectedIndex)) {
            ResetConsoleColor();
        }
    }
}

int Menu::Run() {
    CursorAppear(false);
    int selectedIndex = SelectedIndex;
    bool running = true;

    while (running) {
        ClearScreen();
        std::cout << Prompt << std::endl;
        DisplayOptions();

        int ch = _getch();
        #ifdef _WIN32
            if (ch == 0 || ch == 224) { // Special key prefix in Windows
                ch = _getch(); // Get the actual key code
            }
        #endif

        switch (ch) {
            #ifdef _WIN32
                case KEY_UP:
            #endif
            case 'w':
            case 'W':
                selectedIndex--;
                if (selectedIndex < 0) {
                    selectedIndex = Options.size() - 1;
                }
                break;

            #ifdef _WIN32
                case KEY_DOWN:
            #endif
            case 's':
            case 'S':
                selectedIndex++;
                if (selectedIndex >= static_cast<int>(Options.size())) {
                    selectedIndex = 0;
                }
                break;

            case KEY_ENTER:
                CursorAppear(true);
                return selectedIndex;

            case KEY_ESC:
                CursorAppear(true);
                return -1;
        }
        SelectedIndex = selectedIndex;
    }
    CursorAppear(true);
    return -1;
}

void Menu::RunMainMenu() {
	while (true) {  // Add continuous loop to prevent program exit
		Sleep(1000);
		ClearScreen();
		string Prompt = "******************** MENU GLOWNE ********************";
		vector<string>Options = { 
			"********** OPCJE DOTYCZACE MAPY **********",
			"********** OPCJE DOTYCZACE WINDY **********",
			"********** OPCJE DOTYCZACE ALGORYTMU **********",
			"********** OPCJE DOTYCZACE ZAPYTAN **********",
			"********** OPCJE DOTYCZACE SYMULACJI **********",
			"********** WYJSCIE **********" 
		};
		Menu MainMenu(Prompt, Options);

		int SelectedIndex = MainMenu.Run();

		switch (SelectedIndex) {
		case 0:
			Sleep(1000);
			ClearScreen();
			DisplayMapOptions();
			MenuMapDisplacer();
			break;
		case 1:
			Sleep(1000);
			ClearScreen();
			DisplayElevatorOptions();
			MenuElevatorDisplacer();
			break;
		case 2:
			Sleep(1000);
			ClearScreen();
			DisplayAlgorithmOptions();
			MenuAlgorithmDisplacer();
			break;
		case 3:
			Sleep(1000);
			ClearScreen();
			DisplayEnquiryOptions();
			MenuEnquiryDisplacer();
			break;
		case 4:
			Sleep(1000);
			ClearScreen();
			DisplaySimulationOptions();
			MenuSimulationDisplacer();
			break;
		case 5:
			ExitMenu();
			return;  // Add return statement to properly exit
		}
	}
}

void Menu::DisplayMapOptions() {
	Sleep(1000);
	ClearScreen();
	string Prompt = "******************** MENU DOTYCZACE WEKTORA PIETER ********************";
	vector<string>Options = {"********** DODAJ WEKTOR **********","********** ZMIEN WEKTOR **********", "********** USUN WEKTOR **********", "********** WYSWIETL WEKTOR **********","********** POSORTUJ WEKTOR **********","********** POWROT **********"};
	Menu MapMenu(Prompt, Options);
	
	int SelectedIndex = MapMenu.Run();

	switch (SelectedIndex) {
	case 0:
		ClearScreen();
		DispatcherUnit1.createFloorVector();
		MenuMapDisplacer();
		break;
	case 1:
		ClearScreen();
		DisplayMapChangeOptions();
		break;
	case 2:
		ClearScreen();
		DispatcherUnit1.eraseFloorVector();
		MenuMapDisplacer();
		break;
	case 3:
		ClearScreen();
		DispatcherUnit1.displayFloorVector();
		MenuMapDisplacer();
		break;
	case 4:
		ClearScreen();
		DispatcherUnit1.sortFloorVector();
		MenuMapDisplacer();
		break;
	case 5:
		ClearScreen();
		RunMainMenu();
		//MenuDisplacer();
	}
}

void Menu::DisplayElevatorOptions() {
	Sleep(1000);
	ClearScreen();
	string Prompt = "******************** MENU DOTYCZACE WIND ********************";
	vector<string>Options = { "********** DODAJ WINDE DO WEKTORA **********","********** WYSWIETL WEKTOR WIND **********", "********** USUN WEKTOR WIND **********","********** POWROT **********" };
	Menu ElevatorMenu(Prompt, Options);

	int SelectedIndex = ElevatorMenu.Run();

	switch (SelectedIndex) {
	case 0:
		ClearScreen();
		DispatcherUnit1.addElevatorToVector();
		MenuElevatorDisplacer();
		break;
	case 1:
		ClearScreen();
		Sleep(2000);
		DispatcherUnit1.displayElevatorVector();
		MenuElevatorDisplacer();
		break;
	case 2:
		ClearScreen();
		DispatcherUnit1.clearElevatorVector();
		MenuElevatorDisplacer();
		break;
	case 3:
		ClearScreen();
		RunMainMenu();
		//MenuDisplacer();
	}
}

void Menu::DisplayAlgorithmOptions() {
	Sleep(1000);
	ClearScreen();
	string Prompt = "******************** MENU DOTYCZACE ALGORYTMU ********************";
	vector<string>Options = { "********** ZOBACZ CROSSOVER **********","********** KONFIGURACJA **********","********** TESTOWA SYMULACJA **********","********** WYSWIETL KOLEJKE RUCHOW **********" ,"********** WYSWIETL DNA WYGENEROWANEJ POPULACJI **********","********** TESTOWANIE PLIKU **********","********** POWROT **********" };
	Menu AlgorithmMenu(Prompt, Options);

	int SelectedIndex = AlgorithmMenu.Run();

	switch (SelectedIndex) {
	case 0:
		ClearScreen();
		DispatcherUnit1.callCrossover();
		MenuAlgorithmDisplacer();
		break;
	case 1:
		ClearScreen();
		DispatcherUnit1.callAlgorithmConfiguration();
		MenuAlgorithmDisplacer();
		break;
	case 2:
		ClearScreen();
		DispatcherUnit1.simulationTest();
		MenuAlgorithmDisplacer();
		break;
	case 3:
		ClearScreen();
		DispatcherUnit1.printMoveQueue();
		MenuAlgorithmDisplacer();
		break;
	case 4:
		ClearScreen();
		DispatcherUnit1.printDNA();
		MenuAlgorithmDisplacer();
		break;
	case 5:
		ClearScreen();
		DispatcherUnit1.fileTest();
		MenuAlgorithmDisplacer();
		break;
	case 6:
		ClearScreen();
		MenuDisplacer();
		break;
	}
}

void Menu::DisplayEnquiryOptions() {
	Sleep(1000);
	ClearScreen();
	string Prompt = "******************** MENU DOTYCZACE ZAPYTANIA ********************";
	vector<string>Options = { "********** STWORZ ZAPYTANIA **********","********** WYSWIETLANIE ZAPYTANIA **********","********** DODAJ ZAPYTANIE **********","********** USUN ZAPYTANIE - WYSWIETL **********" ,"********** POWROT **********" };
	Menu EnquiryMenu(Prompt, Options);

	int SelectedIndex = EnquiryMenu.Run();

	switch (SelectedIndex) {
	case 0:
		Sleep(1000);
		ClearScreen();
		DispatcherUnit1.addEnquiryToVector();
		MenuEnquiryDisplacer();
		break;
	case 1:
		Sleep(1000);
		ClearScreen();
		DispatcherUnit1.displayEnquiries();
		MenuEnquiryDisplacer();
		break;
	case 2:
		Sleep(1000);
		ClearScreen();
		DispatcherUnit1.addOneEnquiry();
		MenuEnquiryDisplacer();
		break;
	case 3:
		Sleep(1000);
		ClearScreen();
		DispatcherUnit1.eraseOneEnquiryDisplay();
		MenuEnquiryDisplacer();
		break;
	case 4:
		ClearScreen();
		RunMainMenu();
		break;
	}
}

void Menu::DisplaySimulationOptions() {
    ClearScreen();
    string Prompt = "******************** MENU DOTYCZACE SYMULACJI ********************";
    vector<string>Options = { 
        "********** SYMULACJA - UTWORZENIE SETU DANYCH - CROSSOVERVIEW - WYBRANIE WINDY **********",
        "********** SYMULACJA - STALY SET DANYCH **********", 
        "********** MOVE ELEVATOR MANUAL - TEST - POCZATEK **********",
        "********** MOVE ELEVATOR AUTOMATIC - TEST - POCZATEK **********",
        "********** WLACZ SYMULACJE **********",
        "********** SZYBKA SYMULACJA (DOMYSLNE PARAMETRY) **********",
        "********** POWROT **********" 
    };
    Menu SimulationMenu(Prompt, Options);

    int SelectedIndex = SimulationMenu.Run();

    try {
        switch (SelectedIndex) {
        case 0:
            Sleep(1000);
            ClearScreen();
            DispatcherUnit1.createDefaultRequirements();
            MenuSimulationDisplacer();
            break;
        case 1:
            Sleep(1000);
            ClearScreen();
            DispatcherUnit1.usePreconfiguratedSymulation();
            MenuSimulationDisplacer();
            break;
        case 2:
            Sleep(1000);
            ClearScreen();
            DispatcherUnit1.moveElevatorCarToManual();
            MenuSimulationDisplacer();
            break;
        case 3:
            Sleep(1000);
            ClearScreen();
            DispatcherUnit1.goWithMoveQueue();
            MenuSimulationDisplacer();
            break;
        case 4:
            Sleep(1000);
            ClearScreen();
            DispatcherUnit1.runSimulation();
            MenuSimulationDisplacer();
            break;
        case 5:
            Sleep(1000);
            ClearScreen();
            try {
                std::cout << "Uruchamianie szybkiej symulacji..." << std::endl;
                DispatcherUnit1.usePreconfiguratedSymulation();
                std::cout << "Symulacja zakończona." << std::endl;
                Sleep(2000);
            }
            catch (const std::exception& e) {
                std::cout << "Błąd podczas symulacji: " << e.what() << std::endl;
                Sleep(2000);
            }
            MenuSimulationDisplacer();
            break;
        case 6:
            ClearScreen();
            MenuDisplacer();
            break;
        }
    }
    catch (const std::runtime_error& e) {
        ClearScreen();
        std::cout << "Wystąpił błąd: " << e.what() << std::endl;
        std::cout << "Naciśnij Enter, aby kontynuować..." << std::endl;
        std::cin.get();
        MenuSimulationDisplacer();
    }
    catch (const std::exception& e) {
        ClearScreen();
        std::cout << "Wystąpił nieoczekiwany błąd: " << e.what() << std::endl;
        std::cout << "Naciśnij Enter, aby kontynuować..." << std::endl;
        std::cin.get();
        MenuSimulationDisplacer();
    }
}

void Menu::DisplayMapChangeOptions() {
	Sleep(1000);
	ClearScreen();
	string Prompt = "******************** MENU DOTYCZACE ZMIANY MAPY ********************";
	vector<string>Options = { "********** DODAJ ELEMENT **********","********** USUN ELEMENT **********", "********** USUN GRUPE ELEMENTOW **********","********** POWROT **********" };
	Menu MapChangeMenu(Prompt, Options);

	int SelectedIndex = MapChangeMenu.Run();

	switch (SelectedIndex) {
	case 0:
		Sleep(1000);
		ClearScreen();
		DispatcherUnit1.addFloorVectorElement();
		MenuMapChangeDisplacer();
		break;
	case 1:
		Sleep(1000);
		ClearScreen();
		DispatcherUnit1.eraseFloorVectorElement();
		MenuMapChangeDisplacer();
		break;
	case 2:
		Sleep(1000);
		ClearScreen();
		DispatcherUnit1.eraseGroupFloorVector();
		MenuMapChangeDisplacer();
		break;
	case 3:
		ClearScreen();
		DisplayMapOptions();
		break;
	case 4:
		ClearScreen();
		MenuMapDisplacer();
		break;
	}
}


void Menu::ExitMenu() {
	ClearScreen();
	cout << "WYJSCIE";
	exit(0);
}

//zmienic to na osobna, jedna metode z parametrami
void Menu::MenuDisplacer() {
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	bool flaga = true;
	while (flaga) {
		char ch = GetKeyPress();
		if (ch == '\n' || ch == '\r') {
			flaga = false;
			ClearScreen();
			DisplayOptions();
		}
	}
}

void Menu::MenuMapDisplacer() {
    Sleep(1000);
    bool flaga = true;
    while (flaga) {
        if (IsReturnKeyPressed()) {
            flaga = false;
            ClearScreen();
            DisplayMapOptions();
        }
    }
}

void Menu::MenuElevatorDisplacer() {
    Sleep(1000);
    bool flaga = true;
    while (flaga) {
        if (IsReturnKeyPressed()) {
            flaga = false;
            ClearScreen();
            DisplayElevatorOptions();
        }
    }
}

void Menu::MenuAlgorithmDisplacer() {
	Sleep(1000);
	bool flaga = true;
	while (flaga) {
		if (IsReturnKeyPressed()) {
			flaga = false;
			ClearScreen();
			DisplayAlgorithmOptions();
		}
	}
}

void Menu::MenuEnquiryDisplacer() {
	Sleep(1000);
	bool flaga = true;
	while (flaga) {
		if (IsReturnKeyPressed()) {
			flaga = false;
			ClearScreen();
			DisplayEnquiryOptions();
		}
	}
}

void Menu::MenuSimulationDisplacer() {
	Sleep(1000);
	bool flaga = true;
	while (flaga) {
		if (IsReturnKeyPressed()) {
			flaga = false;
			ClearScreen();
			DisplaySimulationOptions();
		}
	}
}

void Menu::MenuMapChangeDisplacer() {
	Sleep(1000);
	bool flaga = true;
	while (flaga) {
		if (IsReturnKeyPressed()) {
			flaga = false;
			ClearScreen();
			DisplayMapChangeOptions();
		}
	}
}
