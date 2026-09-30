#include <psp2/ctrl.h>

class Input
{
public:
    Input()
    {
        previousButtons = 0;
        pressedButtons = 0;
        sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);
        currentPad = {0};
    }

    void update()
    {
        sceCtrlPeekBufferPositive(0, &currentPad, 1);
        pressedButtons = currentPad.buttons & ~previousButtons;
        previousButtons = currentPad.buttons;
    }

    bool isHeld(unsigned int mask)
    {
        return (currentPad.buttons & mask) != 0;
    }

    bool isPressed(unsigned int mask)
    {
        return (pressedButtons & mask) != 0;
    }

private:
    SceCtrlData currentPad;
    unsigned int previousButtons;
    unsigned int pressedButtons;
};