// SPDX-FileCopyrightText: 2013 Dolphin Emulator Project
// SPDX-FileCopyrightText: 2014 Citra Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include "pch.h"
#include "thread.h"

namespace Common {
    void SetCurrentThreadPriority(ThreadPriority new_priority) {
        auto handle = GetCurrentThread();
        int windows_priority = 0;
        switch (new_priority) {
        case ThreadPriority::Low:
            windows_priority = THREAD_PRIORITY_BELOW_NORMAL;
            break;
        case ThreadPriority::Normal:
            windows_priority = THREAD_PRIORITY_NORMAL;
            break;
        case ThreadPriority::High:
            windows_priority = THREAD_PRIORITY_ABOVE_NORMAL;
            break;
        case ThreadPriority::VeryHigh:
            windows_priority = THREAD_PRIORITY_HIGHEST;
            break;
        case ThreadPriority::Critical:
            windows_priority = THREAD_PRIORITY_TIME_CRITICAL;
            break;
        default:
            windows_priority = THREAD_PRIORITY_NORMAL;
            break;
        }
        SetThreadPriority(handle, windows_priority);
    }
} // namespace Common
