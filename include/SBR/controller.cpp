#include "SBR/controller.h"
#include <stdexcept>
#include <iostream>
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
	js = open(device.str().c_str(), O_RDONLY | O_NONBLOCK);
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

XboxController::~XboxController()
{
#ifdef _WIN64
#elif defined(__linux__)
	close(js);
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
		if (errno != EAGAIN)
			connected = false;
		return;
	}

	// update state accordingly
	if (event.type & JS_EVENT_BUTTON) {
		int mask;
		switch (event.number) {
			case EVENT_NUMBER_GAMEPAD_A:
				mask = GAMEPAD_A;
				break;

			case EVENT_NUMBER_GAMEPAD_B:
				mask = GAMEPAD_B;
				break;

			case EVENT_NUMBER_GAMEPAD_X:
				mask = GAMEPAD_X;
				break;

			case EVENT_NUMBER_GAMEPAD_Y:
				mask = GAMEPAD_Y;
				break;

			case EVENT_NUMBER_GAMEPAD_LEFT_SHOULDER:
				mask = GAMEPAD_LEFT_SHOULDER;
				break;

			case EVENT_NUMBER_GAMEPAD_RIGHT_SHOULDER:
				mask = GAMEPAD_RIGHT_SHOULDER;
				break;

			case EVENT_NUMBER_GAMEPAD_LEFT_THREE:
				mask = GAMEPAD_LEFT_THREE;
				break;

			case EVENT_NUMBER_GAMEPAD_RIGHT_THREE:
				mask = GAMEPAD_RIGHT_THREE;
				break;

			case EVENT_NUMBER_GAMEPAD_SELECT:
				mask = GAMEPAD_SELECT;
				break;

			case EVENT_NUMBER_GAMEPAD_START:
				mask = GAMEPAD_START;
				break;

			case EVENT_NUMBER_GAMEPAD_HOME:
				mask = GAMEPAD_HOME;
				break;
			default:
				break;
		}

		if (event.value)
			buttonState |= mask;
		else
			buttonState &= !mask;
	}
	else if (event.type & JS_EVENT_AXIS) {
		Axis *axis;
		if (event.number == EVENT_NUMBER_GAMEPAD_LEFT_STICK_X ||
			event.number == EVENT_NUMBER_GAMEPAD_LEFT_STICK_Y)
			axis = &leftAnalogAx;
		else if (event.number == EVENT_NUMBER_GAMEPAD_RIGHT_STICK_X ||
				 event.number == EVENT_NUMBER_GAMEPAD_RIGHT_STICK_Y)
			axis = &rightAnalogAx;
		else if (event.number == EVENT_NUMBER_GAMEPAD_LEFT_TRIGGER ||
				 event.number == EVENT_NUMBER_GAMEPAD_RIGHT_TRIGGER)
			axis = &triggerAx;
		else if (event.number == EVENT_NUMBER_GAMEPAD_DPAD_X ||
				 event.number == EVENT_NUMBER_GAMEPAD_DPAD_Y)
			axis = &dpadAx;

		else
		{
			axis = nullptr;
		}

		if (axis!=nullptr) {
			if (event.number % 2 == 0)
				axis->x = event.value;
			else
				axis->y = -event.value;
		}
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
	return (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_X) > 0;
#elif defined(__linux__)
	return buttonState & GAMEPAD_X;
#endif
}

bool XboxController::isYPressed()
{
#ifdef _WIN64
	return (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_Y) > 0;
#elif defined(__linux__)
	return buttonState & GAMEPAD_Y;
#endif
}

bool XboxController::isAPressed()
{
#ifdef _WIN64
	return (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_A) > 0;
#elif defined(__linux__)
	return buttonState & GAMEPAD_A;
#endif
}

bool XboxController::isBPressed()
{
#ifdef _WIN64
	return (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_B) > 0;
#elif defined(__linux__)
	return buttonState & GAMEPAD_B;
#endif
}

bool XboxController::isDPadUpPressed()
{
#ifdef _WIN64
	return (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) > 0;
#elif defined(__linux__)
	return dpadAx.y > 0;
#endif
}

bool XboxController::isDPadDownPressed()
{
#ifdef _WIN64
	return (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) > 0;
#elif defined(__linux__)
	return dpadAx.y < 0;
#endif
}

bool XboxController::isDPadLeftPressed()
{
#ifdef _WIN64
	return (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) > 0;
#elif defined(__linux__)
	return dpadAx.x < 0;
#endif
}

bool XboxController::isDPadRightPressed()
{
#ifdef _WIN64
	return (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) > 0;
#elif defined(__linux__)
	return dpadAx.x > 0;
#endif
}

bool XboxController::isLeftTriggerButtonPressed()
{
#ifdef _WIN64
	return (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) > 0;
#elif defined(__linux__)
	return buttonState & GAMEPAD_LEFT_SHOULDER;
#endif
}

bool XboxController::isRightTriggerButtonPressed()
{
#ifdef _WIN64
	return (_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) > 0;
#elif defined(__linux__)
	return buttonState & GAMEPAD_RIGHT_SHOULDER;
#endif
}

short XboxController::leftStickX()
{
#ifdef _WIN64
	return _controllerState.Gamepad.sThumbLX;
#elif defined(__linux__)
	return leftAnalogAx.x;
#endif
}

short XboxController::leftStickY()
{
#ifdef _WIN64
	return _controllerState.Gamepad.sThumbLY;
#elif defined(__linux__)
	return leftAnalogAx.y;
#endif
}

short XboxController::rightStickX()
{
#ifdef _WIN64
	return _controllerState.Gamepad.sThumbRX;
#elif defined(__linux__)
	return -rightAnalogAx.y;
#endif
}

short XboxController::rightStickY()
{
#ifdef _WIN64
	return _controllerState.Gamepad.sThumbRY;
#elif defined(__linux__)
	return -rightAnalogAx.x;
#endif
}

short XboxController::leftTrigger()
{
#ifdef _WIN64
	return _controllerState.Gamepad.bLeftTrigger * 257 - 32768;
#elif defined(__linux__)
	return triggerAx.x;
#endif
}

short XboxController::rightTrigger()
{
#ifdef _WIN64
	return _controllerState.Gamepad.bRightTrigger * 257 - 32768;
#elif defined(__linux__)
	return -triggerAx.y;
#endif
}
