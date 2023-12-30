#pragma once
#include "pch.h"

class LegacyFrameLimiter
{
private:
    s32 targetTicksToWait, negative_targetTicksToWait, sleepResolution, accumulatedError;
    LARGE_INTEGER clockFrequency{}, nextCounter{}, currentCounter{};

public:
    LegacyFrameLimiter(s64 targetFramerate)
    {
        timeBeginPeriod(1);
        QueryPerformanceFrequency(&clockFrequency);
        UpdateFramerateLimit(targetFramerate);
        SetFrameStart();
    }

    ~LegacyFrameLimiter()
    {
        timeEndPeriod(1);
    }

    inline void UpdateFramerateLimit(s64 targetFramerate)
    {
        targetTicksToWait = (s32)(clockFrequency.QuadPart / targetFramerate);
        negative_targetTicksToWait = -targetTicksToWait;
        sleepResolution = (s32)(clockFrequency.QuadPart / 1000 * 2); // 2ms for sleep(1)
        accumulatedError = 0;
    }

    inline void SetFrameStart()
    {
        QueryPerformanceCounter(&nextCounter);
        nextCounter.QuadPart += (s64)(targetTicksToWait + accumulatedError);
    }

    inline bool ShouldWait()
    {
        QueryPerformanceCounter(&currentCounter);
        bool shouldWait = nextCounter.QuadPart - currentCounter.QuadPart > 0;
        accumulatedError = accumulatedError * shouldWait;
        return shouldWait;
    }

    inline void Wait()
    {
        while (true)
        {
            QueryPerformanceCounter(&currentCounter);
            s32 ticksLeft = (s32)(nextCounter.QuadPart - currentCounter.QuadPart);

            // checks
            if (ticksLeft <= 0)
            {
                accumulatedError = max(negative_targetTicksToWait, ticksLeft);
                break;
            }
            if (ticksLeft > sleepResolution) Sleep(1);
            else for (int i = 0; i < 5; ++i) Sleep(0);
        }
    }
};
