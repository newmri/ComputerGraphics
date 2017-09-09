#include <string>
#include "CVector.h"

int main()
{
	CVector<DATA_TYPE> vector1, vector2;
	cout << "Input vector1: ";
	cin >> vector1;
	cout << "Input vector2: ";
	cin >> vector2;

	string cmdString;

	while (true) {
		cout << "Command Prompt>> ";
		cin >> cmdString;
		if (cmdString == "+") cout << vector1 << " + " << vector2 << " = " << vector1 + vector2<<endl;
		else if (cmdString == "-") cout << vector1 << " - " << vector2 << " = " << vector1 - vector2 << endl;
		else if (cmdString == "d") cout << vector1 << " . " << vector2 << " = " << vector1.CalScalarProduct(vector2) << endl;
		else if (cmdString == "c") cout << vector1 << " * " << vector2 << " = " << vector1 * vector2 << endl;
		else if (cmdString == "l") {
			cout << vector1 << " = root(" << vector1.GetLength() << "), " 
				<< vector2 << " = root(" << vector2.GetLength() << ")" << endl;

		}
	}

}