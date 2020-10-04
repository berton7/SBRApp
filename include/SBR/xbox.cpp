#include "SBR/xbox.h"
#include <stdexcept>
#ifdef __linux__
#include <fcntl.h>
#include <cstdio>
#include <unistd.h>
#include <string>
#include <sstream>
#endif

XboxController::XboxController(int playerNumber) {
	if (playerNumber < 1 || playerNumber > 4) throw std::invalid_argument("Input a playerNumber between 1 and 4");
	_controllerNum = playerNumber - 1;
#ifdef __linux__
	std::ostringstream device;
	device << "/dev/input/js" << _controllerNum;
	js = open(device.str().c_str(), O_RDONLY);
	if (js == -1)
		perror("Could not open joystick");
	else {
		connected = true;
#endif
	update();
#ifdef __linux__
	}
#endif
}

#ifdef _WIN64
XINPUT_STATE XboxController::getState(){
	// Zeroise the state
	ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

	// Get the state
	XInputGetState(_controllerNum, &_controllerState);

	return _controllerState;
}
#endif

void XboxController::update()
{
#ifdef _WIN64
	getState();
#elif defined(__linux__)
	ssize_t bytes;
	bytes = read(js, &event, sizeof(event));
	if (bytes==-1)
	{
		connected = false;
		return;
	}

	// update state accordingly
	switch(event.type)
	{
		case JS_EVENT_BUTTON:
			int mask;
			if (event.number == EVENT_NUMBER_GAMEPAD_A)
				mask = GAMEPAD_A;

			else if (event.number == EVENT_NUMBER_GAMEPAD_Y)
				mask = GAMEPAD_Y;

			else if (event.number == EVENT_NUMBER_GAMEPAD_SELECT)
				mask = GAMEPAD_SELECT;
			/*

			else if (event.number == EVENT_NUMBER_GAMEPAD_A)
				mask = GAMEPAD_A;

			else if (event.number == EVENT_NUMBER_GAMEPAD_A)
				mask = GAMEPAD_A;

			else if (event.number == EVENT_NUMBER_GAMEPAD_A)
				mask = GAMEPAD_A;

			else if (event.number == EVENT_NUMBER_GAMEPAD_A)
				mask = GAMEPAD_A;

			else if (event.number == EVENT_NUMBER_GAMEPAD_A)
				mask = GAMEPAD_A;

			else if (event.number == EVENT_NUMBER_GAMEPAD_A)
				mask = GAMEPAD_A;

			else if (event.number == EVENT_NUMBER_GAMEPAD_A)
				mask = GAMEPAD_A;

			else if (event.number == EVENT_NUMBER_GAMEPAD_A)
				mask = GAMEPAD_A;

			else if (event.number == EVENT_NUMBER_GAMEPAD_A)
				mask = GAMEPAD_A;
			 */

			if (event.value)
				buttonState |= mask;
			else
				buttonState &= !mask;
			break;
		case JS_EVENT_AXIS:
			break;
		case JS_EVENT_INIT:
			break;
		default:
			break;
	}
#endif
}

bool XboxController::isConnected() {
#ifdef _WIN64
	// Zeroise the state
	ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

	// Get the state
	DWORD Result = XInputGetState(_controllerNum, &_controllerState);
	return Result == ERROR_SUCCESS;
#elif defined(__linux__)
	return connected;
#endif
}

int XboxController::playerNumber() const {
	return this->_controllerNum + 1;
}

bool XboxController::isXPressed()
{
#ifdef _WIN64
	return (getState().Gamepad.wButtons & XINPUT_GAMEPAD_X) > 0;
#endif
}

bool XboxController::isYPressed()
{
#ifdef _WIN64
	return (getState().Gamepad.wButtons & XINPUT_GAMEPAD_Y) > 0;
#elif defined(__linux__)
	return buttonState & GAMEPAD_Y;
#endif
}

bool XboxController::isAPressed()
{
#ifdef _WIN64
	return (getState().Gamepad.wButtons & XINPUT_GAMEPAD_A) > 0;
#elif defined(__linux__)
	return buttonState & GAMEPAD_A;
#endif
}

bool XboxController::isBPressed()
{
#ifdef _WIN64
	return (getState().Gamepad.wButtons & XINPUT_GAMEPAD_B) > 0;
#endif
}

bool XboxController::isDPadUpPressed()
{
#ifdef _WIN64
	return (getState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) > 0;
#endif
}

bool XboxController::isDPadDownPressed()
{
#ifdef _WIN64
	return (getState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) > 0;
#endif
}

bool XboxController::isDPadLeftPressed()
{
#ifdef _WIN64
	return (getState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) > 0;
#endif
}

bool XboxController::isDPadRightPressed()
{
#ifdef _WIN64
	return (getState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) > 0;
#endif
}

bool XboxController::isLeftTriggerButtonPressed()
{
#ifdef _WIN64
	return (getState().Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) > 0;
#endif
}

bool XboxController::isRightTriggerButtonPressed()
{
#ifdef _WIN64
	return (getState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) > 0;
#endif
}

short XboxController::leftStickX()
{
#ifdef _WIN64
	return getState().Gamepad.sThumbLX;
#endif
}

short XboxController::leftStickY()
{
#ifdef _WIN64
	return getState().Gamepad.sThumbLY;
#endif
}

short XboxController::rightStickX()
{
#ifdef _WIN64
	return getState().Gamepad.sThumbRX;
#endif
}

short XboxController::rightStickY()
{
#ifdef _WIN64
	return getState().Gamepad.sThumbRY;
#endif
}

byte XboxController::leftTrigger()
{
#ifdef _WIN64
	return getState().Gamepad.bLeftTrigger;
#endif
}

byte XboxController::rightTrigger()
{
#ifdef _WIN64
	return getState().Gamepad.bRightTrigger;
#endif
}