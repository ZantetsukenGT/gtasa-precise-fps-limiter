#pragma once
#include "pch.h"

class CFrameSyncPrecise
{
private:
    int32_t ticksToWait, ticksIn2MS, accumulatedError;
    LARGE_INTEGER cpuFrequency{}, startCounter{}, currentCounter{};

public:
    CFrameSyncPrecise(double targetFramerate)
    {
        timeBeginPeriod(1);
        QueryPerformanceFrequency(&cpuFrequency);
        UpdateFramerateLimit(targetFramerate);
        SetFrameStart();
    }

    ~CFrameSyncPrecise()
    {
        timeEndPeriod(1);
    }

    inline void UpdateFramerateLimit(double targetFramerate)
    {
        ticksToWait = (int32_t)(cpuFrequency.QuadPart / targetFramerate);
        ticksIn2MS = (int32_t)(cpuFrequency.QuadPart / 1000 * 2);
        accumulatedError = 0;
    }

    inline void SetFrameStart()
    {
        QueryPerformanceCounter(&startCounter);
    }

    inline bool ShouldWait()
    {
        QueryPerformanceCounter(&currentCounter);
        int32_t ticksPassed = (int32_t)(currentCounter.QuadPart - startCounter.QuadPart);
        int32_t ticksLeft = ticksToWait - ticksPassed + accumulatedError;
        return ticksLeft > 0;
    }

    inline void Wait()
    {
        while (true)
        {
            QueryPerformanceCounter(&currentCounter);
            int32_t ticksPassed = (int32_t)(currentCounter.QuadPart - startCounter.QuadPart);
            int32_t ticksLeft = ticksToWait - ticksPassed + accumulatedError;
            /*printf("tTW:%d, tP:%d, tL:%d, err:%d\n",
                ticksToWait,
                ticksPassed,
                ticksLeft,
                accumulatedError
            );*/

            // checks
            if (ticksLeft <= 0)
            {
                accumulatedError = ticksLeft;
                break;
            }
            if (ticksLeft > ticksIn2MS) Sleep(1);
            else for (int i = 0; i != 10; ++i) Sleep(0);
        }
    }
};
