#include "xbox.h"
#include <stdexcept>

#ifdef _WIN32
XboxController::XboxController(int playerNumber)
{
	if (playerNumber < 1 || playerNumber > 4) throw std::invalid_argument("Input a playerNumber between 1 and 4");
	_controllerNum = playerNumber-1;
}

XINPUT_STATE XboxController::getState(){
	// Zeroise the state
	ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

	// Get the state
	XInputGetState(_controllerNum, &_controllerState);

	return _controllerState;
}

bool XboxController::isConnected() {
	// Zeroise the state
	ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

	// Get the state
	DWORD Result = XInputGetState(_controllerNum, &_controllerState);
	return Result == ERROR_SUCCESS;
}

int XboxController::playerNumber() {
	return this->_controllerNum + 1;
}

bool XboxController::isXPressed()
{
	return (getState().Gamepad.wButtons & XINPUT_GAMEPAD_X) > 0;
}
bool XboxController::isYPressed()
{
	return (getState().Gamepad.wButtons & XINPUT_GAMEPAD_Y) > 0;
}
bool XboxController::isAPressed()
{
	return (getState().Gamepad.wButtons & XINPUT_GAMEPAD_A) > 0;
}
bool XboxController::isBPressed()
{
	return (getState().Gamepad.wButtons & XINPUT_GAMEPAD_B) > 0;
}

bool XboxController::isDPadUpPressed()
{
	return (getState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) > 0;
}

bool XboxController::isDPadDownPressed()
{
	return (getState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) > 0;
}

bool XboxController::isDPadLeftPressed()
{
	return (getState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) > 0;
}

bool XboxController::isDPadRightPressed()
{
	return (getState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) > 0;
}

bool XboxController::isLeftTriggerButtonPressed()
{
	return (getState().Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) > 0;
}

bool XboxController::isRightTriggerButtonPressed()
{
	return (getState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) > 0;
}

short XboxController::leftStickX()
{
	return getState().Gamepad.sThumbLX;
}

short XboxController::leftStickY()
{
	return getState().Gamepad.sThumbLY;
}

short XboxController::rightStickX()
{
	return getState().Gamepad.sThumbRX;
}

short XboxController::rightStickY()
{
	return getState().Gamepad.sThumbRY;
}

byte XboxController::leftTrigger()
{
	return getState().Gamepad.bLeftTrigger;
}

byte XboxController::rightTrigger()
{
	return getState().Gamepad.bRightTrigger;
}

#endif
