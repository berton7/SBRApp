#ifndef SBR_XBOX_H
#define SBR_XBOX_H
#ifdef _WIN64
#include <Windows.h>
#include <Xinput.h>
#elif defined(__linux__)
#include <bitset>
#include <linux/joystick.h>
#define EVENT_NUMBER_GAMEPAD_A 0
#define EVENT_NUMBER_GAMEPAD_B 1
#define EVENT_NUMBER_GAMEPAD_X 2
#define EVENT_NUMBER_GAMEPAD_Y 3
#define EVENT_NUMBER_GAMEPAD_LEFT_SHOULDER 4
#define EVENT_NUMBER_GAMEPAD_RIGHT_SHOULDER 5
#define EVENT_NUMBER_GAMEPAD_SELECT 6
#define EVENT_NUMBER_GAMEPAD_START 7
#define EVENT_NUMBER_GAMEPAD_HOME 8
#define EVENT_NUMBER_GAMEPAD_LEFT_THREE 9
#define EVENT_NUMBER_GAMEPAD_RIGHT_THREE 10
#define EVENT_NUMBER_GAMEPAD_LEFT_STICK_X 0
#define EVENT_NUMBER_GAMEPAD_LEFT_STICK_Y 1
#define EVENT_NUMBER_GAMEPAD_RIGHT_STICK_X 3
#define EVENT_NUMBER_GAMEPAD_RIGHT_STICK_Y 4
#define EVENT_NUMBER_GAMEPAD_LEFT_TRIGGER 2
#define EVENT_NUMBER_GAMEPAD_RIGHT_TRIGGER 5
#define EVENT_NUMBER_GAMEPAD_DPAD_X 6
#define EVENT_NUMBER_GAMEPAD_DPAD_Y 7
#define GAMEPAD_A 0x400
#define GAMEPAD_B 0x200
#define GAMEPAD_X 0x100
#define GAMEPAD_Y 0x80
#define GAMEPAD_LEFT_SHOULDER 0x40
#define GAMEPAD_RIGHT_SHOULDER 0x20
#define GAMEPAD_SELECT 0x10
#define GAMEPAD_START 0x8
#define GAMEPAD_HOME 0x4
#define GAMEPAD_LEFT_THREE 0x2
#define GAMEPAD_RIGHT_THREE 0x1
#endif

#ifdef __linux__
typedef std::bitset<8> byte;

class Axis
{
public:
	uint16_t x, y;
};
#endif

class XboxController {
private:
	int _controllerNum;
#ifdef _WIN64
    XINPUT_STATE _controllerState;
	XINPUT_STATE getState();
#elif defined(__linux__)
	int js;
	bool connected;
	struct js_event event;
	uint16_t buttonState;
	Axis leftAnalogAx, rightAnalogAx, leftTriggerAx, rightTriggerAx, dpadAx;
#endif
public:
    XboxController(int playerNumber = 1);

    void update();

    bool isConnected();

    int playerNumber() const;

    bool isXPressed();
    bool isYPressed();
    bool isAPressed();
    bool isBPressed();

    bool isDPadUpPressed();
    bool isDPadDownPressed();
    bool isDPadLeftPressed();
    bool isDPadRightPressed();

    bool isLeftTriggerButtonPressed();
    bool isRightTriggerButtonPressed();
        
    short leftStickX();
    short leftStickY();
    short rightStickX();
    short rightStickY();

    byte leftTrigger();
    byte rightTrigger();
};

#endif
