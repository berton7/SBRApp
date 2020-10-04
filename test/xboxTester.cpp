#include <iostream>
#ifdef __linux__
#include <memory>
#include <unistd.h>
#define Sleep(ms) (usleep(ms * 1000))
#endif
#include "SBR/xbox.h"


int main()
{
	std::unique_ptr<XboxController> x;
	for (int i = 1; i < 5; i++) {
		x = std::make_unique<XboxController>(i);
		if (x->isConnected()) {
			break;
		}
	}
	int n;
	while (!x->isConnected()) {
		std::cout << "No controller revealed. Are you sure you connected one?" << std::endl;
		std::cout << "If so, please input the player number: ";
		std::cin >> n;
		if (n < 1 || n>4)
			do {
				std::cout << "Please input a number between 1 and 4: ";
				std::cin >> n;
			} while (n < 1 || n>4);
		x = std::make_unique<XboxController>(n);
	}


	std::cout << "Controller for player " << x->playerNumber() << " succesfully added." << std::endl;
	while (x->isConnected()) {
		x->update();
		std::cout << "\r";
		
		std::cout << x->isXPressed() << x->isYPressed() << x->isAPressed() << x->isBPressed();
		std::cout << x->isDPadLeftPressed() << x->isDPadUpPressed() << x->isDPadDownPressed() << x->isDPadRightPressed();
		std::cout << x->isLeftTriggerButtonPressed() << x->isRightTriggerButtonPressed();


		std::cout << " " << x->leftStickX() << " " << x->leftStickY() << " " << x->rightStickX() << " " << x->rightStickY();

		std::cout << " " << x->leftTrigger() << " " << x->rightTrigger();

		std::cout << "                    ";

#ifdef __linux__
		fflush(stdout);
#endif
		Sleep(10);
	}

	std::cout << std::endl << "Controller disconnected." << std::endl;
#ifdef _WIN64
	system("pause");
#endif
	return 0;
}
