#include <iostream>
#include "SBR/xbox.h"
//#include "serial.h"

using namespace std;

int main() {
	unique_ptr<XboxController> x;
	for (int i = 1; i < 5; i++) {
		x = make_unique<XboxController>(i);
		if (x->isConnected()) {
			break;
		}
	}
	bool useController = true;
	if (!x->isConnected()) {
		string s;
		cout << "No controller found. Do you want to continue without a controller? (y/n):";
		cin >> s;
		while (s != "y" && s != "n") {
			cout << "Only y/n allowed: ";
			cin >> s;
		}
		useController = (s == "y");
	}

	if (useController) {
		cout << "Using controller" << endl;
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
	}
	else {
		cout << "Not using controller" << endl;

	}
}
