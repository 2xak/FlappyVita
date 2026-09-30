#include <psp2/ctrl.h>
#include <psp2/rtc.h>
#include <psp2/kernel/threadmgr.h>

#include "Input.h"
#include "Timer.h"
#include "Level.h"
#include "Bird.h"

int main() {
    // Initialize the Vita2D library
    vita2d_init();

    Timer timer;
    Bird bird;
    Input input;
    Level level;
    
    // Main loop
    while (1) {
        if (bird.isCollided()) {
            input.update();
            if (input.isPressed(SCE_CTRL_CROSS))
                break;
            sceKernelDelayThread(16000);
        }
        else {
            timer.update();

            float deltaTime = timer.getDeltaTime();

            // Clear the screen
            vita2d_start_drawing();
            vita2d_clear_screen();

            input.update();
            bird.update(input, level, deltaTime);

            // End drawing and swap buffers
            vita2d_end_drawing();
            vita2d_swap_buffers();
        }
        
    }

    // Clean up and exit
    vita2d_fini();
    return 0;
}

