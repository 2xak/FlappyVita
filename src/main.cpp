#include <psp2/ctrl.h>
#include <psp2/rtc.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/kernel/threadmgr.h>
#include <vita2d.h>
#include <stdio.h>

#include "Input.h"
#include "Timer.h"
#include "Level.h"
#include "Bird.h"

void drawScores(vita2d_pgf *font, int score, int highScore)
{
    char scoreText[32];
    char highScoreText[32];
    snprintf(scoreText, sizeof(scoreText), "Score: %d", score);
    snprintf(highScoreText, sizeof(highScoreText), "Best: %d", highScore);
    vita2d_pgf_draw_text(font, 20, 32, RGBA8(255, 255, 255, 255), 1.0f, scoreText);
    vita2d_pgf_draw_text(font, 20, 58, RGBA8(255, 255, 255, 255), 1.0f, highScoreText);
}

int main()
{
    // Initialize the Vita2D library
    vita2d_init();
    vita2d_pgf *font = vita2d_load_default_pgf();

    Timer timer;
    Bird bird;
    Input input;
    Level level;
    int highScore = 0;

    // Main loop
    while (1)
    {
        if (bird.isCollided())
        {
            timer.update();
            input.update();
            if (input.isPressed(SCE_CTRL_CROSS))
                bird.reset(level);

            vita2d_start_drawing();
            vita2d_clear_screen();
            bird.draw(level);
            drawScores(font, level.getScore(), highScore);
            vita2d_pgf_draw_text(font, 340, 280, RGBA8(255, 255, 255, 255), 1.0f,
                                 "Press X to start/restart");
            vita2d_end_drawing();
            vita2d_swap_buffers();
            sceKernelDelayThread(16000);
        }
        else
        {
            timer.update();
            float deltaTime = timer.getDeltaTime();

            vita2d_start_drawing();
            vita2d_clear_screen();
            input.update();
            bird.update(input, level, deltaTime);
            if (level.getScore() > highScore)
                highScore = level.getScore();
            drawScores(font, level.getScore(), highScore);
            vita2d_end_drawing();
            vita2d_swap_buffers();
        }
    }

    // Clean up
    vita2d_free_pgf(font);
    vita2d_fini();
    sceKernelExitProcess(0);
    return 0;
}
