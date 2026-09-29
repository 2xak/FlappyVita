#include <vita2d.h>
#include <stdlib.h>
#include <deque>

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 544

class Level {
public:
    Level() {
        sectionHeights = { 0, 0, 0, 0, 0 };
        sectionWidth =  (float)SCREEN_WIDTH / (float)(sectionHeights.size() - 1);
    }
    void update(float offset, float deltaTime) {
        levelPosition = offset * deltaTime;
    }

    void repeatCheck() {
        levelPosition -= sectionWidth;
        sectionHeights.pop_front();
        int i = rand() % (SCREEN_HEIGHT - 20);
    }
private:
    float sectionWidth;
    std::deque<int> sectionHeights;
    float levelPosition = 0.0f;
};