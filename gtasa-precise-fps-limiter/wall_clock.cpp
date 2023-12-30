// SPDX-FileCopyrightText: Copyright 2020 yuzu Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include "pch.h"
#ifndef WIN8_1_AND_LOWER_COMPAT
#include "steady_clock.h"
#include "wall_clock.h"

namespace Common {

class StandardWallClock final : public WallClock {
public:
    explicit StandardWallClock() : start_time{SteadyClock::Now()} {}

    std::chrono::nanoseconds GetTimeNS() const override {
        return SteadyClock::Now() - start_time;
    }

private:
    SteadyClock::time_point start_time;
};

std::unique_ptr<WallClock> CreateStandardWallClock() {
    return std::make_unique<StandardWallClock>();
}
} // namespace Common
#endif
