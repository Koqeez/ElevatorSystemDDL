#include "DispatcherUnit.h"
#include <string>
#include <vector>
using namespace std;

//W PRZYSZLOSCI -- FLUSH BUFFERA IO

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

	void DisplayMapChangeOptions();

	void DisplayInformation();

	void MenuDisplacer();
	void MenuMapDisplacer();
	void MenuElevatorDisplacer();
	void MenuAlgorithmDisplacer();
	void MenuEnquiryDisplacer();
	void MenuMapChangeDisplacer();
};