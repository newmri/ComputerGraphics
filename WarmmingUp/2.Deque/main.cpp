#include <string>
#include "CDeque.h"

int main()
{
	CDeque<DATA_TYPE> deque;
	Pos<DATA_TYPE> pos;
	string cmdString;
	DATA_TYPE tpos[3]{};

	while (true) {
		cout << "Command Prompt>> ";
		cin >> cmdString;

		if (cmdString == "+") {
			cin >> tpos[0]>>tpos[1]>>tpos[2];
			pos.x = tpos[0];
			pos.y = tpos[1];
			pos.z = tpos[2];

			deque.AddRear(pos);
			deque.DisplayAll();
		}
		else if (cmdString == "-") {
			deque.RemoveRear();
			deque.DisplayAll();
		}
		else if (cmdString == "e") {
			cin >> tpos[0] >> tpos[1] >> tpos[2];
			pos.x = tpos[0];
			pos.y = tpos[1];
			pos.z = tpos[2];

			deque.AddFront(pos);
			deque.DisplayAll();
		}
		else if (cmdString == "d") {
			deque.RemoveFront();
			deque.DisplayAll();
		}
		else if (cmdString == "l") cout << "Length: " << deque.Size() << endl;
		else if (cmdString == "c") {
			deque.RemoveAll();
			deque.DisplayAll();
		}
		else if (cmdString == "n") deque.PeekNearest();
		else if (cmdString == "m") deque.PeekFurtherMost();
		else if (cmdString == "q") return true;
		else cout << "Error" << endl;

	}
}