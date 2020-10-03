#ifndef SBR_XBOX_H
#define SBR_XBOX_H
#ifdef _WIN64
    #include <Windows.h>
    #include <Xinput.h>
#endif

class XboxController {
private:
	int _controllerNum;
#ifdef _WIN64
    XINPUT_STATE _controllerState;
	XINPUT_STATE getState();
#endif
public:
    XboxController(int playerNumber = 1);

    void update();

    bool isConnected();

    int playerNumber();

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
