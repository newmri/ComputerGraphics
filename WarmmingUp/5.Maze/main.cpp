#include <string>
#include "CMazeGenerator.h"

int main()
{
	CMazeGenerator cMazeGenerator;
	string cmdString;

	cout << "Input width and height sequentially" << endl;
	cout << "Command Prompt>> ";
	cin >> cMazeGenerator;
	while (true) {
		cout << "Input g to generate new maze" << endl;
		cout << "Command Prompt>> ";
		cin >> cmdString;
		if (cmdString == "g") {
			cMazeGenerator.Init();
			cMazeGenerator.Draw();
		}
		else cout << "Error" << endl;
	}
}