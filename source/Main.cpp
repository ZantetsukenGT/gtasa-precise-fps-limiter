#pragma comment(lib, "winmm.lib")

#include "plugin.h"

#include <d3d9.h>

#include "FileSystem/Config.h"
#include "FileSystem/Logging.h"

#include "NtSleep/HighQoS.h"
#include "NtSleep/LegacyFrameLimiter.h"

#include "RenderWare/renderware_hook.h"

#include "SAMP/cchat_unofficial.h"
#include "SAMP/samp_hook.h"

using namespace plugin;

class PreciseFramerateLimiter {
    static inline constexpr D3DCOLOR PREFIX_COLOR = 0x88AA62FF;
    static inline constexpr size_t   GTASA_ID3D9DEVICE_ADDRESS = 0xC97C28;

    static inline int                g_FramerateValue = 144;

    static inline LegacyFrameLimiter legacyFrameLimiter{ g_FramerateValue };

    static void WINAPIV newFpsLimitCommand(const char* str)
    {
        auto len = strlen(str);
        if (!len)
        {
            return;
        }

        int framerate;
        try
        {
            framerate = std::stoi(str);
        }
        catch (std::exception const&)
        {
            cchat_unofficial::AddMessage(PREFIX_COLOR, "Framerate limiter v2: valid amounts are 20+ or 0 for unlimited");
            return;
        }

        if (framerate == Config::UNLIMITED_FRAMERATE)
        {
            cchat_unofficial::AddMessage(PREFIX_COLOR, "Framerate limiter v2: unlimited");
            Config::WriteFramerateLimit(framerate);
            SetFrameRate(framerate);
            return;
        }

        if (framerate < Config::MINIMUM_FRAMERATE)
        {
            cchat_unofficial::AddMessage(PREFIX_COLOR, "Framerate limiter v2: valid amounts are 20+ or 0 for unlimited");
            return;
        }

        std::string message("Framerate limiter v2: " + std::to_string(framerate));
        cchat_unofficial::AddMessage(PREFIX_COLOR, message.c_str());
        Config::WriteFramerateLimit(framerate);
        SetFrameRate(framerate);
    }

    using PVoidFunctionNoArgs = void(__cdecl*)();
    static inline PVoidFunctionNoArgs originalCGameProcessFromSamp = nullptr;

    // Why vendor agnostic? because implementing both AMD's AntiLag 2 or NVIDIA's Reflex looks exactly like this and may be introduced in the future.
    static void __cdecl cGameProcessFromSamp_VendorAgnosticHook() {
        if (g_FramerateValue) {
            // Do Sleep
            legacyFrameLimiter.Wait();
        }
        originalCGameProcessFromSamp();
    }

public:
	PreciseFramerateLimiter() {
        SetHighQoS();
        renderware_hook::ReplaceRwSetRefreshRate();

        Events::initRwEvent += [] {
            SetFrameRate(Config::ReadFramerateLimit());

            size_t sampBaseAddress = samp_hook::GetBase();
            if (sampBaseAddress)
            {
                samp_hook::RemoveSampLimits();
                samp_hook::ReplaceSampFpsLimitCommand((PBYTE)newFpsLimitCommand);

                size_t cGameProcessFromSamp = samp_hook::FindCGameProcessFromSamp();
                if (!cGameProcessFromSamp) {
                    Logging::WriteLine("Cannot install mod: Couldn't find SA-MP's CGame::Process function. Use an official client! https://github.com/openmultiplayer/launcher/releases/latest");
                    return;
                }
                originalCGameProcessFromSamp = reinterpret_cast<PVoidFunctionNoArgs>(DetourFunction((PBYTE)cGameProcessFromSamp, (PBYTE)cGameProcessFromSamp_VendorAgnosticHook));
            }
            else
            {
                Events::gameProcessEvent.before += [] {
                    if (g_FramerateValue) {
                        // Do Sleep
                        legacyFrameLimiter.Wait();
                    }
                };
            }
        };
	};

    static void SetFrameRate(int framerate)
    {
        g_FramerateValue = framerate;

        if (framerate) {
            legacyFrameLimiter.UpdateFramerateLimit(framerate);
        }
    }
} PreciseFramerateLimiter;

extern "C" __declspec(dllexport) void __cdecl PreciseFramerateLimiter_SetFrameRate(int framerate) {
    PreciseFramerateLimiter::SetFrameRate(framerate);
}
