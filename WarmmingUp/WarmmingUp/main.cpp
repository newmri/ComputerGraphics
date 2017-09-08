#include <string>

#include "CMatrix.h"
#include "Cmatrix.cpp"

int main()
{
	CMatrix<int> cMatrix;
	string cmdString;
	while (true) {
		cout << "Command Prompt>> ";
		cin >> cmdString;
		if (cmdString == "M" || cmdString == "m") cMatrix.Multi();
		else if(cmdString == "A" || cmdString == "a") cMatrix.Add();
		else if(cmdString == "D" || cmdString == "d") cMatrix.Min();
		else if(cmdString == "R" || cmdString == "r") cMatrix.DisplayDeterminant();
		else if(cmdString == "H" || cmdString == "h") cMatrix.ChangeMatrix();
		else cout << "Input m or a or d or r or h" << endl;

	}
	system("pause");
}
