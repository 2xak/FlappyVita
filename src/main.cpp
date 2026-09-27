#include <vita2d.h>
#include <psp2/ctrl.h>
#include <psp2/rtc.h>

#include "Timer.h"
#include "Input.h"

int main() {
    // Initialize the Vita2D library
    vita2d_init();

    Timer timer;
    Input input;
    
    // Main loop
    while (1) {
        timer.update();
        input.update();

        float deltaTime = timer.getDeltaTime();

        // Clear the screen
        vita2d_start_drawing();
        vita2d_clear_screen();

        // Draw something (e.g., a rectangle)
        vita2d_draw_rectangle(100, 100, 200, 200, RGBA8(255, 0, 0, 255));

        // End drawing and swap buffers
        vita2d_end_drawing();
        vita2d_swap_buffers();
    }

    // Clean up and exit
    vita2d_fini();
    return 0;
}

