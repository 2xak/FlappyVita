#include <vita2d.h>
#include <stdlib.h>
#include <list>

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 544
#define PIPE_COLOR RGBA8(0, 255, 0, 255)

class Level {
public:
    Level() {
        sectionHeights = { 0, 0, 0, 0 };
        sectionWidth =  (float)SCREEN_WIDTH / (float)(sectionHeights.size() - 1);
    }
    void update(float offset, float deltaTime) {
        levelPosition += offset * deltaTime;
    }

    void repeatCheck() {
        if (levelPosition > sectionWidth) {
            levelPosition -= sectionWidth;
            sectionHeights.pop_front();
            int i = rand() % (SCREEN_HEIGHT - 100);
            if (i <= 10) i = 0;
            sectionHeights.push_back(i);
        }
    }

    void drawLevel() {
        int section = 0;
        
        for (auto s : sectionHeights) {
            if (s != 0) {
                    vita2d_draw_rectangle(section * sectionWidth + (sectionWidth - pipeWidth) / 2.0f - levelPosition, SCREEN_HEIGHT - s, pipeWidth, s, PIPE_COLOR);
                    vita2d_draw_rectangle(section * sectionWidth + (sectionWidth - pipeWidth) / 2.0f - levelPosition, 0, pipeWidth, SCREEN_HEIGHT - s - 200, PIPE_COLOR);

            }
            section++;
        } 
    }
private:
    const float pipeWidth = 50.0f;
    float sectionWidth;
    std::list<int> sectionHeights;
    float levelPosition = 0.0f;
};
