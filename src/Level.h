#include <vita2d.h>
#include <stdlib.h>
#include <list>

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 544
#define PIPE_COLOR RGBA8(0, 255, 0, 255)

class Level
{
public:
    Level()
    {
        sectionHeights = {0, 0, 0, 0};
        sectionScored = {false, false, false, false};
        sectionWidth = (float)SCREEN_WIDTH / (float)(sectionHeights.size() - 1);
    }
    void update(float offset, float deltaTime, float birdX)
    {
        levelPosition += offset * deltaTime;

        int section = 0;
        auto scored = sectionScored.begin();
        for (int pipeHeight : sectionHeights)
        {
            float pipeX = section * sectionWidth + (sectionWidth - pipeWidth) / 2.0f - levelPosition;
            if (pipeHeight != 0 && !*scored && pipeX + pipeWidth <= birdX)
            {
                *scored = true;
                currentScore++;
            }
            scored++;
            section++;
        }
    }

    void repeatCheck()
    {
        while (levelPosition > sectionWidth)
        {
            levelPosition -= sectionWidth;
            sectionHeights.pop_front();
            sectionScored.pop_front();
            int i = rand() % (SCREEN_HEIGHT - 250);
            if (i <= 10)
                i = 0;
            sectionHeights.push_back(i);
            sectionScored.push_back(false);
        }
    }

    int getScore() const { return currentScore; }

    void drawLevel() const
    {
        int section = 0;

        for (auto s : sectionHeights)
        {
            if (s != 0)
            {
                vita2d_draw_rectangle(section * sectionWidth + (sectionWidth - pipeWidth) / 2.0f - levelPosition, SCREEN_HEIGHT - s, pipeWidth, s, PIPE_COLOR);
                vita2d_draw_rectangle(section * sectionWidth + (sectionWidth - pipeWidth) / 2.0f - levelPosition, 0, pipeWidth, SCREEN_HEIGHT - s - 200, PIPE_COLOR);
            }
            section++;
        }
    }

    bool collides(float x, float y, float width, float height) const
    {
        int section = 0;
        for (int pipeHeight : sectionHeights)
        {
            if (pipeHeight != 0)
            {
                float pipeX = section * sectionWidth + (sectionWidth - pipeWidth) / 2.0f - levelPosition;
                float topPipeHeight = SCREEN_HEIGHT - pipeHeight - 200;

                if (overlaps(x, y, width, height,
                             pipeX, SCREEN_HEIGHT - pipeHeight,
                             pipeWidth, pipeHeight) ||
                    overlaps(x, y, width, height,
                             pipeX, 0, pipeWidth, topPipeHeight))
                {
                    return true;
                }
            }
            section++;
        }
        return false;
    }

    void reset()
    {
        sectionHeights = {0, 0, (rand() % (SCREEN_HEIGHT - 250) <= 10) ? 0 : rand() % (SCREEN_HEIGHT - 250), (rand() % (SCREEN_HEIGHT - 250) <= 10) ? 0 : rand() % (SCREEN_HEIGHT - 250)};
        sectionScored = {false, false, false, false};
        levelPosition = 0.0f;
        currentScore = 0;
    }

private:
    static bool overlaps(float ax, float ay, float aw, float ah,
                         float bx, float by, float bw, float bh)
    {
        return ax < bx + bw && ax + aw > bx && ay < by + bh && ay + ah > by;
    }

    const float pipeWidth = 50.0f;
    float sectionWidth;
    std::list<int> sectionHeights;
    std::list<bool> sectionScored;
    float levelPosition = 0.0f;
    int currentScore = 0;
};
