#ifndef SBR_XBOX_H
#define SBR_XBOX_H
#ifdef _WIN32
    #include <Windows.h>
    #include <Xinput.h>
#endif

class XboxController {
private:
    XINPUT_STATE _controllerState;
    int _controllerNum;
public:
    XboxController(int playerNumber = 1);
    XINPUT_STATE getState();
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
