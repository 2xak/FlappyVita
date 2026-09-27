#include <psp2/ctrl.h>
#include <cstring>

class Input {
public:
    Input() : previousButtons(0) {
        sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);
        currentPad = {0};
    }

    void update() {
        previousButtons = currentPad.buttons;
        sceCtrlPeekBufferPositive(0, &currentPad, 1);
    }

    bool isHeld(unsigned int mask){
        return (currentPad.buttons & mask) != 0;
    }

    bool isPressed(unsigned int mask) {
        unsigned int pressedButtons = currentPad.buttons & ~previousButtons;
        return (pressedButtons & mask) != 0;
    }
private:
    SceCtrlData currentPad;
    unsigned int previousButtons;
};