// SPDX-FileCopyrightText: Copyright 2020 yuzu Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "pch.h"

namespace Common {

class WallClock {
public:
    virtual ~WallClock() = default;

    /// @returns The time in nanoseconds since the construction of this clock.
    virtual std::chrono::nanoseconds GetTimeNS() const = 0;
};

std::unique_ptr<WallClock> CreateStandardWallClock();
} // namespace Common
