#pragma once
#include "pch.h"
#include "util.h"
#include "LegacyFrameLimiter.h"
#ifndef WIN8_1_AND_LOWER_COMPAT
#include "ModernFrameLimiter.h"
#else
#include "thread.h"
#endif

using namespace plugin;

#define SA_DEVICE_ADDRESS 0xC97C28
#define ENDSCENE_INDEX 42

namespace d3d9_hook
{
	using EndSceneType = HRESULT(__stdcall*)(IDirect3DDevice9* this_) noexcept;
    EndSceneType oEndScene = nullptr;

    LegacyFrameLimiter legacyLimiter(422);
#ifndef WIN8_1_AND_LOWER_COMPAT
    ModernFrameLimiter modernLimiter(422);
#endif
    bool enableFramerateLimit;

    inline void ChangeFramerate(s64 newFramerate)
    {
        enableFramerateLimit = true;
        legacyLimiter.UpdateFramerateLimit(newFramerate);
#ifndef WIN8_1_AND_LOWER_COMPAT
        modernLimiter.UpdateFramerateLimit(newFramerate);
#endif
    }

    inline void UnlimitFramerate()
    {
        enableFramerateLimit = false;
    }

    HRESULT __stdcall hkEndScene(IDirect3DDevice9* this_) noexcept
    {
        auto hr = oEndScene(this_);
        if (enableFramerateLimit)
        {
            if (legacyLimiter.ShouldWait())
                legacyLimiter.Wait();
            legacyLimiter.SetFrameStart();
        }
        return hr;
    }

    inline void ReplaceD3D9Device(s64 framerate)
    {
        enableFramerateLimit = !!framerate;
        if (enableFramerateLimit)
        {
            ChangeFramerate(framerate);
        }

#ifdef WIN8_1_AND_LOWER_COMPAT
        Common::SetCurrentThreadPriority(Common::ThreadPriority::VeryHigh);
        // https://learn.microsoft.com/en-us/windows/win32/procthread/quality-of-service
        PROCESS_POWER_THROTTLING_STATE PowerThrottling{
            .Version{PROCESS_POWER_THROTTLING_CURRENT_VERSION},
            .ControlMask{PROCESS_POWER_THROTTLING_EXECUTION_SPEED |
                         PROCESS_POWER_THROTTLING_IGNORE_TIMER_RESOLUTION},
            .StateMask{},
        };
        SetProcessInformation(GetCurrentProcess(), ProcessPowerThrottling, &PowerThrottling,
            sizeof(PROCESS_POWER_THROTTLING_STATE));
#endif

        EndSceneType originalEndScene = (EndSceneType)GetVMT(*(void**)SA_DEVICE_ADDRESS, ENDSCENE_INDEX);
        oEndScene = (EndSceneType)DetourFunction((PBYTE)originalEndScene, (PBYTE)hkEndScene);
    }
};

