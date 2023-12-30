#pragma once

#include "pch.h"
#include "wall_clock.h"
#include "thread.h"
#include "timer_resolution.h"

class ModernFrameLimiter
{
private:
    std::unique_ptr<Common::WallClock> clock_;
    s64 timer_resolution_, target_wait_time_, next_time_, accumulated_error_;

public:
    ModernFrameLimiter(s64 targetFramerate)
        : clock_{ Common::CreateStandardWallClock() }
    {
        UpdateFramerateLimit(targetFramerate);
        SetFrameStart();
    }

    inline void UpdateFramerateLimit(s64 targetFramerate)
    {
        Common::SetCurrentThreadPriority(Common::ThreadPriority::VeryHigh);
        Common::Windows::SetCurrentTimerResolutionToMaximum();
        timer_resolution_ = Common::Windows::GetCurrentTimerResolution().count() * 3;

        target_wait_time_ = std::nano::den / targetFramerate;
        accumulated_error_ = 0;
    }

    inline void SetFrameStart()
    {
        next_time_ = clock_->GetTimeNS().count() + target_wait_time_ + accumulated_error_;
    }

    inline bool ShouldWait()
    {
        return next_time_ - clock_->GetTimeNS().count() > 0;
    }

    inline void Wait()
    {
        while (true)
        {
            auto wait_time = next_time_ - clock_->GetTimeNS().count();
            if (wait_time <= 0)
            {
                accumulated_error_ = wait_time;
                break;
            }

            if (wait_time > timer_resolution_) Common::Windows::SleepForOneTick();
            else std::this_thread::yield();
        }
    }
};
