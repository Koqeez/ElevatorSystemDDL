#include <string>
#include <vector>
using namespace std;

class Menu {
	int SelectedIndex;
	vector<string>Options;
	string Prompt;


public:
	Menu();
	Menu(string prompt_a, vector<string>& options_a);
	
	void DisplayOptions();
	//sporo mozliwosci z win.h

	int Run();
	void RunMainMenu();
};