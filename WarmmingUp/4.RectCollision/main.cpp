#include <string>
#include "CRect.h"

int main()
{

	CRect<DATA_TYPE> rect1, rect2;

	int choice{};
	string cmdString;

	while (true) {
		cout << "(1 (rectangle X rectangle)" << endl;
		cout << "(Command: a(left) / d(right) /s(down) /w(up))" << endl;
		cout << "Input Shape Combination: ";
		cin >> choice;
		if (choice == 1) {
			cout << "Input Shape1: ";
			cin >> rect1;
			cout << "Input Shape2: ";
			cin >> rect2;
			break;
		}
	}
	while (true) {
		cout << "Command Prompt>> ";
		cin >> cmdString;

	}

	return 0;
}