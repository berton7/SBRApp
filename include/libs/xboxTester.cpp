#include <iostream>
#include "xbox.h"

using namespace std;

int main()
{
	unique_ptr<XboxController> x;
	for (int i = 1; i < 5; i++) {
		x = make_unique<XboxController>(i);
		if (x->isConnected()) {
			break;
		}
	}
	int n;
	while (!x->isConnected()) {
		cout << "No controller revealed. Are you sure you connected one?" << endl;
		cout << "If so, please input the player number: ";
		cin >> n;
		if (n < 1 || n>4)
			do {
				cout << "Please input a number between 1 and 4: ";
				cin >> n;
			} while (n < 1 || n>4);
		x = make_unique<XboxController>(n);
	}


	cout << "Controller for player " << x->playerNumber() << " succesfully added." << endl;
	while (x->isConnected()) {
		cout << "\r";
		
		cout << x->isXPressed() << x->isYPressed() << x->isAPressed() << x->isBPressed();
		cout << x->isDPadLeftPressed() << x->isDPadUpPressed() << x->isDPadDownPressed() << x->isDPadRightPressed();
		cout << x->isLeftTriggerButtonPressed() << x->isRightTriggerButtonPressed();
		
		cout << " " << x->leftStickX() << " " << x->leftStickY() << " " << x->rightStickX() << " " << x->rightStickY();
		
		cout << " " << (short)x->leftTrigger() << " " << (short)x->rightTrigger();

		cout << "                    ";
		Sleep(10);
	}


	cout << endl << "Controller disconnected." << endl;
	system("pause");
	return 0;
}
