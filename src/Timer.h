#include <psp2/rtc.h>

class Timer
{
private:
    SceRtcTick lastTick;
    float deltaTime;

public:
    Timer() : deltaTime(0.0f)
    {
        sceRtcGetCurrentTick(&lastTick);
    }

    void update()
    {
        SceRtcTick currentTick;
        sceRtcGetCurrentTick(&currentTick);

        // Calculate the difference in ticks
        SceUInt64 tickDifference = currentTick.tick - lastTick.tick;

        // Convert ticks to seconds (assuming 1 tick = 1/1000000 seconds)
        deltaTime = static_cast<float>(tickDifference) / 1000000.0f;

        // Update last tick
        lastTick = currentTick;
    }

    float getDeltaTime() const
    {
        return deltaTime;
    }
};