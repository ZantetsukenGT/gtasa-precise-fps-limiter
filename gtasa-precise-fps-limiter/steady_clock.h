// SPDX-FileCopyrightText: Copyright 2023 yuzu Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "pch.h"

namespace Common {

struct SteadyClock {
    using rep = s64;
    using period = std::nano;
    using duration = std::chrono::nanoseconds;
    using time_point = std::chrono::time_point<SteadyClock>;

    static constexpr bool is_steady = true;

    [[nodiscard]] static time_point Now() noexcept;
};

} // namespace Common
