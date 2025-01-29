#pragma once
#include "DispatcherUnit.h"
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#else
using WORD = unsigned short;
using DWORD = unsigned long;
#endif

class Menu {
private:
    std::string Prompt;
    std::vector<std::string> Options;
    int SelectedIndex;
    DispatcherUnit DispatcherUnit1;

    void PrintMenu(int selectedIndex);
    void DisplayOptions();
    char GetKeyPress();
    void ClearScreen();

public:
    Menu(std::string prompt_a, std::vector<std::string>& options_a);
    Menu();
    ~Menu();
    
    int Run();
    void RunMainMenu();
    void DisplayMapOptions();
    void DisplayElevatorOptions();
    void DisplayAlgorithmOptions();
    void DisplayEnquiryOptions();
    void DisplaySimulationOptions();
    void DisplayMapChangeOptions();
    
    void ExitMenu();
    void MenuDisplacer();
    void MenuMapDisplacer();
    void MenuElevatorDisplacer();
    void MenuAlgorithmDisplacer();
    void MenuEnquiryDisplacer();
    void MenuSimulationDisplacer();
    void MenuMapChangeDisplacer();
};

// Platform-independent helper functions
void ClearScreen();
void CursorAppear(bool visible);
void SetConsoleColour(WORD* Attributes, DWORD Colour);
void ResetConsoleColour(WORD Attributes);
bool IsReturnKeyPressed(); 