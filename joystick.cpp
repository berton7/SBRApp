#include "SBR/xbox.h"
#include <iostream>
#include <unistd.h>
#include <string>

int main()
{
	XboxController c;
	while (c.isConnected())
	{
		c.update();
		std::string s = c.isYPressed() ? "true": "false";
		std::cout << "\r" << s;
		fflush(stdout);
		usleep(1000);
	}
}
