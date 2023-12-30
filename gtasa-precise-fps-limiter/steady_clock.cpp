// SPDX-FileCopyrightText: Copyright 2023 yuzu Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include "pch.h"
#ifndef WIN8_1_AND_LOWER_COMPAT
#include "steady_clock.h"

namespace Common {
    static s64 WindowsQueryPerformanceFrequency() {
        LARGE_INTEGER frequency;
        QueryPerformanceFrequency(&frequency);
        return frequency.QuadPart;
    }

    static s64 WindowsQueryPerformanceCounter() {
        LARGE_INTEGER counter;
        QueryPerformanceCounter(&counter);
        return counter.QuadPart;
    }

    SteadyClock::time_point SteadyClock::Now() noexcept {
        static const auto freq = WindowsQueryPerformanceFrequency();
        const auto counter = WindowsQueryPerformanceCounter();

        // 10 MHz is a very common QPC frequency on modern PCs.
        // Optimizing for this specific frequency can double the performance of
        // this function by avoiding the expensive frequency conversion path.
        static constexpr s64 TenMHz = 10'000'000;

        if (freq == TenMHz) [[likely]] {
            static_assert(period::den % TenMHz == 0);
            static constexpr s64 Multiplier = period::den / TenMHz;
            return time_point{duration{counter * Multiplier}};
        }

        const auto whole = (counter / freq) * period::den;
        const auto part = (counter % freq) * period::den / freq;
        return time_point{duration{whole + part}};
    }
}; // namespace Common
#endif
