#include <vita2d.h>

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 544
#define BIRD_COLOR RGBA8(255, 255, 0, 255)

class Bird
{
public:
    Bird() : birdPosition(SCREEN_HEIGHT / 2.0f), birdVelocity(0.0f), birdAcceleration(0.0f) {};

    void update(Input input, Level &level, float deltaTime)
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

        int birdX = SCREEN_WIDTH / 5.0f;
        level.update(140.0f, deltaTime, birdX);

        level.repeatCheck();

        if (birdPosition < 0 || birdPosition + 20 > SCREEN_HEIGHT || level.collides(birdX, birdPosition, 20, 20))
        {
            collided = true;
        }

        draw(level);
    };

    void draw(Level &level)
    {
        int birdX = SCREEN_WIDTH / 5.0f;
        vita2d_draw_rectangle(birdX, birdPosition, 20, 20, BIRD_COLOR);
        level.drawLevel();
    }

    bool isCollided()
    {
        return collided;
    };

    void reset(Level &level)
    {
        collided = false;
        level.reset();
        birdVelocity = 0.0f;
        birdAcceleration = 0.0f;
        birdPosition = SCREEN_HEIGHT / 2.0f;
    };

private:
    float birdPosition;
    float birdVelocity;
    float birdAcceleration;
    bool collided = true;

    float birdGravity = 1800.0f;
};
