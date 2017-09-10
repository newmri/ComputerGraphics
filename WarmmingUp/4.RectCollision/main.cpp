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
			cout << "Shape 1: " << rect1;
			cout << "Shape 2: " << rect2 << endl;
			break;
		}
	}
	while (true) {
		cout << "Command Prompt>> ";
		cin >> cmdString;
		if (cmdString == "a") {
			rect2.Move(MOVE::LEFT);
			cout << "Shape 1: " << rect1;
			cout << "Shape 2: " << rect2 << endl;
			if (rect2.CheckCollision(rect1)) cout << "Rect 1 & Rect 2 Collide!" << endl;
		}
		else if (cmdString == "d") {
			rect2.Move(MOVE::RIGHT);
			cout << "Shape 1: " << rect1;
			cout << "Shape 2: " << rect2 << endl;
			rect2.CheckCollision(rect1);
			if (rect2.CheckCollision(rect1)) cout << "Rect 1 & Rect 2 Collide!" << endl;
		}
		else if (cmdString == "w") {
			rect2.Move(MOVE::UP);
			cout << "Shape 1: " << rect1;
			cout << "Shape 2: " << rect2 << endl;
			rect2.CheckCollision(rect1);
			if (rect2.CheckCollision(rect1)) cout << "Rect 1 & Rect 2 Collide!" << endl;
		}
		else if (cmdString == "s") {
			rect2.Move(MOVE::DOWN);
			cout << "Shape 1: " << rect1;
			cout << "Shape 2: " << rect2 << endl;
			rect2.CheckCollision(rect1);
			if (rect2.CheckCollision(rect1)) cout << "Rect 1 & Rect 2 Collide!" << endl;
		}
		else cout << "Error" << endl;

	}

	return 0;
}