#include "DispatcherUnit.h"
#include <string>
#include <vector>
using namespace std;


class Menu {
	int SelectedIndex;
	vector<string>Options;
	string Prompt;

	DispatcherUnit DispatcherUnit1;



public:
	Menu();
	Menu(string prompt_a, vector<string>& options_a);
	~Menu();
	
	void DisplayOptions();
	//sporo mozliwosci z win.h

	int Run();

	void RunMainMenu();
	void ExitMenu();

	void DisplayMapOptions();
	void DisplayElevatorOptions();
	void DisplayAlgorithmOptions();
	void DisplayEnquiryOptions();
	void DisplaySimulationOptions();

	void DisplayMapChangeOptions();

	void MenuDisplacer();
	void MenuMapDisplacer();
	void MenuElevatorDisplacer();
	void MenuAlgorithmDisplacer();
	void MenuEnquiryDisplacer();
	void MenuSimulationDisplacer();
	void MenuMapChangeDisplacer();
};