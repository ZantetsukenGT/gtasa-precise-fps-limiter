#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>

void SetHighQoS() {
    HANDLE hProcess = GetCurrentProcess();

    SetPriorityClass(hProcess, HIGH_PRIORITY_CLASS);

    // https://learn.microsoft.com/en-us/windows/win32/procthread/quality-of-service
    PROCESS_POWER_THROTTLING_STATE PowerThrottling{
        .Version{PROCESS_POWER_THROTTLING_CURRENT_VERSION},
        .ControlMask{PROCESS_POWER_THROTTLING_EXECUTION_SPEED |
                     PROCESS_POWER_THROTTLING_IGNORE_TIMER_RESOLUTION},
        .StateMask{},
    };
    SetProcessInformation(hProcess, ProcessPowerThrottling, &PowerThrottling,
        sizeof(PROCESS_POWER_THROTTLING_STATE));
}
