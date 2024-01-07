#include "pch.h"
#include "memory.h"
#include "d3d9_hook.h"
#include "renderware_hook.h"
#include "cchat_unofficial.h"
#include "util.h"

using namespace plugin;

#define CFGFILE_PATH ".\\PreciseFramerateLimiter.cfg"
#define DEFAULT_FRAMERATE 60
#define MINIMUM_FRAMERATE 20
#define PREFIX_COLOR 0x88AA62FF

class PreciseFramerateLimiter
{
    static void RemoveSampLimits()
    {
        auto samp_pointer = sampapi::GetBase();
        if (!samp_pointer)
        {
            Events::initRwEvent -= RemoveSampLimits;
            return;
        }

        DWORD old_prot;

        unsigned long sampProcessFrameLimiterCaller = mem_find_pattern("\x89\x65\xE8\x8B\x0D\xAC\xEB\x26\x10\x85\xC9\x74\x05\xE8", "xxxxx????xxxxx", samp_pointer, 1204224) + 0x3;
        if (sampProcessFrameLimiterCaller - 0x3 && VirtualProtect((void*)sampProcessFrameLimiterCaller, 15, PAGE_EXECUTE_READWRITE, &old_prot))
        {
            DWORD new_prot = old_prot;
            memset(reinterpret_cast<void*>(sampProcessFrameLimiterCaller), 0x90, 15);
            VirtualProtect((void*)sampProcessFrameLimiterCaller, 15, new_prot, &old_prot);
        }

        unsigned long hardcodedSleep1 = mem_find_pattern("\xBA\x80\x1A\x56\x00\xFF\xE2", "xxxxxxx", samp_pointer, 1204224) - 0x7;
        if (hardcodedSleep1 + 0x7 && VirtualProtect((void*)hardcodedSleep1, 1, PAGE_EXECUTE_READWRITE, &old_prot))
        {
            DWORD new_prot = old_prot;
            mem_put<unsigned char>(hardcodedSleep1, 0x0);
            VirtualProtect((void*)hardcodedSleep1, 1, new_prot, &old_prot);
        }

        unsigned long anAddressWithinFpslimitCommand = mem_find_pattern("\x83\xC4\x04\x83\xFE\x14\x72\x3F\x83\xFE\x5A\x77\x3A", "xxxxxxx?xxxx?", samp_pointer, 1204224);
        if (anAddressWithinFpslimitCommand)
        {
            unsigned long fpslimitCommand = mem_find_pattern_backwards_starting_at("\x51\x56\x8B\x74\x24\x0C\x8B\xC6\x8D\x50\x01\xEB", "xxxxxxxxxxxx", samp_pointer, anAddressWithinFpslimitCommand);
            if (fpslimitCommand)
            {
                DetourFunction((PBYTE)fpslimitCommand, (PBYTE)fpslimit_hook);
            }

            unsigned long cchatRefAddressStart = mem_find_pattern("\x56\x68\xF0\x9E\x0E\x10\x50", "xx????x", anAddressWithinFpslimitCommand, 1204224) - 0x1;
            if (cchatRefAddressStart + 0x1)
            {
                DWORD cchatRefAddress = DWORD(*(unsigned char*)cchatRefAddressStart) << 24;
                cchatRefAddress += DWORD(*(unsigned char*)(cchatRefAddressStart - 1)) << 16;
                cchatRefAddress += DWORD(*(unsigned char*)(cchatRefAddressStart - 2)) << 8;
                cchatRefAddress += DWORD(*(unsigned char*)(cchatRefAddressStart - 3));
                cchat_unofficial::SetCChatRef(cchatRefAddress);

                unsigned long anAddressWithinAddMessage = mem_find_pattern("\x2B\xC2\x3D\x90\x00\x00\x00\x77", "xxxxxxxx", samp_pointer, 1204224);
                if (anAddressWithinAddMessage)
                {
                    unsigned long addMessageAddress = mem_find_pattern_backwards_starting_at("\x56", "x", samp_pointer, anAddressWithinAddMessage);
                    if (addMessageAddress)
                    {
                        cchat_unofficial::SetAddMessageAddress(addMessageAddress);
                    }
                }
            }
        }
        
        Events::initRwEvent -= RemoveSampLimits;
    }

    static void ReplaceD3D9Device()
    {
        s64 framerate = ReadFramerateLimit();

        d3d9_hook::ReplaceD3D9Device(framerate);

        Events::drawingEvent -= ReplaceD3D9Device;
    }

    //static int WINAPIV fpslimit_hook(char* str)
    static void WINAPIV fpslimit_hook(const char* str)
    {
        auto len = strlen(str);
        if (!len)
        {
            return;
        }
        s64 framerate = MINIMUM_FRAMERATE - 1;
        try
        {
            std::string _str(str);
            framerate = std::stoll(_str);
        }
        catch (std::exception const&)
        {
        }
        if (framerate && framerate < MINIMUM_FRAMERATE)
        {
            cchat_unofficial::AddMessage(PREFIX_COLOR, "Framerate limiter: valid amounts are 20+ or 0 for unlimited");
            return;
        }
        std::string message("Framerate limiter: " + (framerate ? (std::to_string(framerate)) : "unlimited"));
        cchat_unofficial::AddMessage(PREFIX_COLOR, message.c_str());

        if (!framerate)
        {
            d3d9_hook::UnlimitFramerate();
            WriteFramerateLimit(framerate);
            return;
        }
        d3d9_hook::ChangeFramerate(framerate);
        WriteFramerateLimit(framerate);
    }

    static s64 ReadFramerateLimit()
    {
        std::ifstream cfgFile(CFGFILE_PATH);
        if (cfgFile)
        {
            std::string line;
            std::getline(cfgFile, line);
            cfgFile.close();

            s64 framerate = MINIMUM_FRAMERATE - 1;
            try
            {
                framerate = std::stoll(line);
                if (!framerate)
                {
                    return 0;
                }
            }
            catch (std::exception const&)
            {
            }
            if (framerate < MINIMUM_FRAMERATE)
            {
                framerate = DEFAULT_FRAMERATE;
                WriteFramerateLimit(DEFAULT_FRAMERATE);
            }
            return framerate;
        }
        WriteFramerateLimit(DEFAULT_FRAMERATE);
        return DEFAULT_FRAMERATE;
    }

    static void WriteFramerateLimit(s64 value)
    {
        std::ofstream cfgFile(CFGFILE_PATH, std::ios::out | std::ios::trunc);
        if (cfgFile)
        {
            cfgFile << std::to_string(value) << std::endl;
            cfgFile.close();
        }
    }

public:
    PreciseFramerateLimiter()
    {
        //enable_console();
        renderware_hook::ReplaceRwSetRefreshRate();
        Events::drawingEvent += ReplaceD3D9Device;
        Events::initRwEvent += RemoveSampLimits;
    };

} PreciseFramerateLimiterPlugin;
