#include "SBR/xbox.h"
#include <stdexcept>

XboxController::XboxController(int playerNumber)
{
	if (playerNumber < 1 || playerNumber > 4) throw std::invalid_argument("Input a playerNumber between 1 and 4");
	_controllerNum = playerNumber-1;
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
#endif
}

bool XboxController::isConnected() {
#ifdef _WIN64
	// Zeroise the state
	ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

	// Get the state
	DWORD Result = XInputGetState(_controllerNum, &_controllerState);
	return Result == ERROR_SUCCESS;
#endif
}

int XboxController::playerNumber() {
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
#endif
}
bool XboxController::isAPressed()
{
#ifdef _WIN64
	return (getState().Gamepad.wButtons & XINPUT_GAMEPAD_A) > 0;
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
