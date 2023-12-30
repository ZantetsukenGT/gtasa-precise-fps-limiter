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
    static inline u8 sampVersion = 0;

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
        switch (sampProcessFrameLimiterCaller - samp_pointer)
        {
        case 0x9D9C6:
            sampVersion = 0x1;
            break;
        case 0x9DAF6:
            sampVersion = 0x2;
            break;
        case 0xA1F16:
        case 0xA1F56:
            sampVersion = 0x3;
            break;
        case 0xA2696:
            sampVersion = 0x4;
            break;
        case 0xA2686:
            sampVersion = 0x5;
            break;
        case 0xA23F6:
            sampVersion = 0xD1;
            break;
        }
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

        DWORD offset = 0;
        switch (sampVersion)
        {
        case 0x1:
            offset = 0x64C60;
            break;
        case 0x2:
            offset = 0x64D30;
            break;
        case 0x3:
            offset = 0x68160;
            break;
        case 0x4:
            offset = 0x68890;
            break;
        case 0x5:
            offset = 0x688D0;
            break;
        case 0xD1:
            offset = 0x68310;
            break;
        }
        if (offset)
        {
            DetourFunction(PBYTE(samp_pointer + offset), (PBYTE)fpslimit_hook);
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
            switch (sampVersion)
            {
            case 0x1:
                sampapi::v037r1::RefChat()->AddMessage(PREFIX_COLOR, "Frame Limiter: valid amounts are 20+ or 0 for unlimited");
                break;
            case 0x2:
                cchat_unofficial::AddMessageR2(PREFIX_COLOR, "Frame Limiter: valid amounts are 20+ or 0 for unlimited");
                break;
            case 0x3:
                sampapi::v037r3::RefChat()->AddMessage(PREFIX_COLOR, "Frame Limiter: valid amounts are 20+ or 0 for unlimited");
                break;
            case 0x4:
                cchat_unofficial::AddMessageR4(PREFIX_COLOR, "Frame Limiter: valid amounts are 20+ or 0 for unlimited");
                break;
            case 0x5:
                sampapi::v037r5::RefChat()->AddMessage(PREFIX_COLOR, "Frame Limiter: valid amounts are 20+ or 0 for unlimited");
                break;
            case 0xD1:
                cchat_unofficial::AddMessageDL(PREFIX_COLOR, "Frame Limiter: valid amounts are 20+ or 0 for unlimited");
                break;
            }
            return;
        }
        std::string message("Frame limiter: " + (framerate ? (std::to_string(framerate)) : "unlimited"));
        switch (sampVersion)
        {
        case 0x1:
            sampapi::v037r1::RefChat()->AddMessage(PREFIX_COLOR, message.c_str());
            break;
        case 0x2:
            cchat_unofficial::AddMessageR2(PREFIX_COLOR, message.c_str());
            break;
        case 0x3:
            sampapi::v037r3::RefChat()->AddMessage(PREFIX_COLOR, message.c_str());
            break;
        case 0x4:
            cchat_unofficial::AddMessageR4(PREFIX_COLOR, message.c_str());
            break;
        case 0x5:
            sampapi::v037r5::RefChat()->AddMessage(PREFIX_COLOR, message.c_str());
            break;
        case 0xD1:
            cchat_unofficial::AddMessageDL(PREFIX_COLOR, message.c_str());
            break;
        }

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
