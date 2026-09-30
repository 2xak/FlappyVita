#include <vita2d.h>

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 544
#define BIRD_COLOR RGBA8(255, 255, 0, 255)

class Bird
{
public:
    Bird() : birdPosition(SCREEN_HEIGHT / 2.0f), birdVelocity(0.0f), birdAcceleration(0.0f) {};

    void update(const Input &input, float deltaTime)
    {
        if (input.isPressed(SCE_CTRL_CROSS) && birdVelocity >= birdGravity / 10.0f)
        {
            birdAcceleration = 0.0f;
            birdVelocity = -birdGravity / 5.0f;
        }
        else
            birdAcceleration += birdGravity * deltaTime;

        if (birdAcceleration > birdGravity)
            birdAcceleration = birdGravity;

        birdVelocity += birdAcceleration * deltaTime;
        birdPosition += birdVelocity * deltaTime;
    }

    void draw() const
    {
        vita2d_draw_rectangle(x(), y(), width(), height(), BIRD_COLOR);
    }

    float x() const { return SCREEN_WIDTH / 5.0f; }
    float y() const { return birdPosition; }
    float width() const { return 20.0f; }
    float height() const { return 20.0f; }

    void reset()
    {
        birdPosition = SCREEN_HEIGHT / 2.0f;
        birdVelocity = 0.0f;
        birdAcceleration = 0.0f;
    }

private:
    float birdPosition = SCREEN_HEIGHT / 2.0f;
    float birdVelocity = 0.0f;
    float birdAcceleration = 0.0f;

    float birdGravity = 1800.0f;
};
