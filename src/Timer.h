#include <psp2/rtc.h>

class Timer {
private:
  SceRtcTick lastTick;
  float deltaTime;

public:
  Timer() : deltaTime(0.0f) { sceRtcGetCurrentTick(&lastTick); }

  void update() {
    SceRtcTick currentTick;
    sceRtcGetCurrentTick(&currentTick);

    SceUInt64 tickDifference = currentTick.tick - lastTick.tick;

    deltaTime = static_cast<float>(tickDifference) / 1000000.0f;

    lastTick = currentTick;
  }

  float getDeltaTime() const { return deltaTime; }
};