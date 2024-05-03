#pragma once
#include "pch.h"

class LegacyFrameLimiter
{
private:
    s32 targetTicksToWait_, sleepResolution_;
    LARGE_INTEGER nextCounter_;
public:
    LegacyFrameLimiter(s64 targetFramerate)
    {
        timeBeginPeriod(1);
        UpdateFramerateLimit(targetFramerate);
        QueryPerformanceCounter(&nextCounter_);
        nextCounter_.QuadPart += targetTicksToWait_;
    }

    ~LegacyFrameLimiter()
    {
        timeEndPeriod(1);
    }

    inline void UpdateFramerateLimit(s64 targetFramerate)
    {
        LARGE_INTEGER clockFrequency;
        QueryPerformanceFrequency(&clockFrequency);
        targetTicksToWait_ = (s32)(clockFrequency.QuadPart / targetFramerate);
        sleepResolution_ = (s32)(clockFrequency.QuadPart / 1000 * 2); // 2ms for sleep(1)
    }

    inline void Wait()
    {
        LARGE_INTEGER currentCounter;
        LARGE_INTEGER nextCounter = nextCounter_;
        const s32 targetTicksToWait = targetTicksToWait_;
        const s32 negative_targetTicksToWait = -targetTicksToWait_;
        const s32 sleepResolution = sleepResolution_;

        QueryPerformanceCounter(&currentCounter);
        const s64 ticksLeft64 = nextCounter.QuadPart - currentCounter.QuadPart;
        if (ticksLeft64 > 0)
        {
            s32 ticksLeft = (s32)ticksLeft64;
            // Sleep if the amount of time to sleep is longer
            // than the time the function calls are likely going to take
            while (ticksLeft > sleepResolution)
            {
                Sleep(1);

                QueryPerformanceCounter(&currentCounter);
                ticksLeft = (s32)(nextCounter.QuadPart - currentCounter.QuadPart);
            }

            // Busy-wait until we have slept long enough
            while (ticksLeft > 0)
            {
                Sleep(0); // std::this_thread::yield();

                QueryPerformanceCounter(&currentCounter);
                ticksLeft = (s32)(nextCounter.QuadPart - currentCounter.QuadPart);
            }
            s32 accumulatedError = max(negative_targetTicksToWait, ticksLeft);
            nextCounter_.QuadPart = currentCounter.QuadPart + (s64)(targetTicksToWait + accumulatedError);
        }
        else
        {
            s64 accumulatedError = max((s64)negative_targetTicksToWait, ticksLeft64);
            nextCounter_.QuadPart = currentCounter.QuadPart + targetTicksToWait + accumulatedError;
        }
    }
};
