#include "pch.h"
#include "d3d9_proxy.h"
#include "memory.h"
#include "util.h"

using namespace plugin;

#define SA_DEVICE_ADDRESS 0xC97C28
#define CFGFILE_PATH ".\\PreciseFramerateLimiter.cfg"
#define DEFAULT_FRAMERATE 60
#define MINIMUM_FRAMERATE 20
#define PREFIX_COLOR 0x88AA62FF
#define CHAT_COLOR "{88AA62}"

class PreciseFramerateLimiter
{
    static inline DWORD samp_pointer = NULL;
    static inline CFrameSyncPrecise* frameLimiter = nullptr;
    static inline uint8_t sampVersion = 0;

    static void RemoveSampLimits()
    {
        //enable_console();
        samp_pointer = sampapi::GetBase();
        if (!samp_pointer)
        {
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
        }
        if (offset)
        {
            DetourFunction(PBYTE(samp_pointer + offset), (PBYTE)fpslimit_hook);
        }

        Events::initRwEvent -= RemoveSampLimits;
    }

    static void ReplaceD3D9Device()
    {
        unsigned long framerate = ReadFramerateLimit();
        frameLimiter = new CFrameSyncPrecise(framerate);

        // primero obtenemos el puntero al device del juego y lo alojamos en dev
        IDirect3DDevice9* dev = *(IDirect3DDevice9**)SA_DEVICE_ADDRESS;

        // reemplazamos el ptr con una instancia de device proxy, a la cual tmb le pasaremos el valor original
        // del device para que sepa adonde hacer las calls originales
        *(IDirect3DDevice9**)SA_DEVICE_ADDRESS = new d3d9_device_proxy(*dev, *frameLimiter);

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
        unsigned long framerate = MINIMUM_FRAMERATE - 1;
        try
        {
            std::string _str(str);
            framerate = std::stol(_str);
        }
        catch (std::exception const&)
        {
        }
        if (framerate < MINIMUM_FRAMERATE)
        {
            switch (sampVersion)
            {
            case 0x1:
                sampapi::v037r1::RefChat()->AddChatMessage(nullptr, PREFIX_COLOR, CHAT_COLOR"Frame Limiter: valid amounts are 20+");
                break;
            case 0x2:
            {
                //unknown address for CChat object
                //((void(__thiscall*)(void*, const char*, D3DCOLOR, const char*))(samp_pointer + 0x64D30))((void*)0x26EB80??, nullptr, PREFIX_COLOR, CHAT_COLOR"Frame Limiter: valid amounts are 20+");
            }
            break;
            case 0x3:
                sampapi::v037r3::RefChat()->AddChatMessage(nullptr, PREFIX_COLOR, CHAT_COLOR"Frame Limiter: valid amounts are 20+");
                break;
            case 0x4:
            {
                //unknown address for CChat object
                //((void(__thiscall*)(void*, const char*, D3DCOLOR, const char*))(samp_pointer + 0x64D30))((void*)0x26EB80??, nullptr, PREFIX_COLOR, CHAT_COLOR"Frame Limiter: valid amounts are 20+");
            }
            break;
            case 0x5:
                sampapi::v037r5::RefChat()->AddChatMessage(nullptr, PREFIX_COLOR, CHAT_COLOR"Frame Limiter: valid amounts are 20+");
                break;
            }
            return;
        }
        std::string message(CHAT_COLOR"Frame limiter: " + std::to_string(framerate));
        switch (sampVersion)
        {
        case 0x1:
            sampapi::v037r1::RefChat()->AddChatMessage(nullptr, PREFIX_COLOR, message.c_str());
            break;
        case 0x2:
        {
            //unknown address for CChat object
            //((void(__thiscall*)(void*, const char*, D3DCOLOR, const char*))(samp_pointer + 0x64D30))((void*)0x26EB80??, nullptr, PREFIX_COLOR, message.c_str());
        }
            break;
        case 0x3:
            sampapi::v037r3::RefChat()->AddChatMessage(nullptr, PREFIX_COLOR, message.c_str());
            break;
        case 0x4:
        {
            //unknown address for CChat object
            //((void(__thiscall*)(void*, const char*, D3DCOLOR, const char*))(samp_pointer + 0x64D30))((void*)0x26EB80??, nullptr, PREFIX_COLOR, message.c_str());
        }
            break;
        case 0x5:
            sampapi::v037r5::RefChat()->AddChatMessage(nullptr, PREFIX_COLOR, message.c_str());
            break;
        }
        frameLimiter->UpdateFramerateLimit(static_cast<double>(framerate));
        WriteFramerateLimit(framerate);
    }

    static unsigned long ReadFramerateLimit()
    {
        std::ifstream cfgFile(CFGFILE_PATH);
        if (cfgFile)
        {
            std::string line;
            std::getline(cfgFile, line);
            cfgFile.close();

            long framerate = MINIMUM_FRAMERATE - 1;
            try
            {
                framerate = std::stol(line);
            }
            catch (std::exception const&)
            {
            }
            if (framerate < MINIMUM_FRAMERATE)
            {
                framerate = DEFAULT_FRAMERATE;
                WriteFramerateLimit(DEFAULT_FRAMERATE);
            }
            return static_cast<unsigned long>(framerate);
        }
        WriteFramerateLimit(DEFAULT_FRAMERATE);
        return DEFAULT_FRAMERATE;
    }

    static void WriteFramerateLimit(unsigned long value)
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
        Events::drawingEvent += ReplaceD3D9Device;
        Events::initRwEvent += RemoveSampLimits;
    };

} PreciseFramerateLimiterPlugin;
