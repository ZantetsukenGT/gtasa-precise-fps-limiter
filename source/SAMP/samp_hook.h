#pragma once

#include <Psapi.h>

#include "MemoryUtils/memory.h"
#include "Detours/detours.h"

#include "FileSystem/Config.h"

namespace samp_hook
{
    static size_t baseAddress = 0;
    static size_t sizeOfImage = 0;

    static size_t GetBase() {
        HMODULE hModule = GetModuleHandleA("samp.dll");
        sizeOfImage = 0;

        if (hModule) {
            MODULEINFO mi = {};
            HANDLE hProcess = GetCurrentProcess();

            GetModuleInformation(hProcess, hModule, &mi, sizeof(MODULEINFO));

            sizeOfImage = mi.SizeOfImage;
        }

        baseAddress = reinterpret_cast<size_t>(hModule);

        return baseAddress;
    }

    static size_t FindCGameProcessFromSamp()
    {
        if (!baseAddress)
        {
            return 0;
        }

        size_t anAddressWithinCGameProcessFromSamp = mem_find_pattern("\xA1\x00\x00\x00\x00\x50\x64\x89\x25\x00\x00\x00\x00\x83\xEC\x0C\x53\x56\x57", "xxxxxxxxxxxxxxxxxxx", baseAddress, sizeOfImage);
        if (anAddressWithinCGameProcessFromSamp)
        {
            size_t cGameProcessFromSamp = mem_find_pattern_backwards_starting_at("\x55\x8B\xEC", "xxx", baseAddress, anAddressWithinCGameProcessFromSamp);
            if (cGameProcessFromSamp)
            {
                return cGameProcessFromSamp;
            }
        }
        return 0;
    }

    static void ReplaceSampFpsLimitCommand(PBYTE newFpsLimitCommand)
    {
        if (!baseAddress)
        {
            return;
        }

        unsigned long anAddressWithinFpslimitCommand = mem_find_pattern("\x83\xC4\x04\x83\xFE\x14\x72\x3F\x83\xFE\x5A\x77\x3A", "xxxxxxx?xxxx?", baseAddress, sizeOfImage);
        if (anAddressWithinFpslimitCommand)
        {
            unsigned long fpslimitCommand = mem_find_pattern_backwards_starting_at("\x51\x56\x8B\x74\x24\x0C\x8B\xC6\x8D\x50\x01\xEB", "xxxxxxxxxxxx", baseAddress, anAddressWithinFpslimitCommand);
            if (fpslimitCommand)
            {
                DetourFunction((PBYTE)fpslimitCommand, newFpsLimitCommand);
            }

            unsigned long cchatRefAddressStart = mem_find_pattern("\x56\x68\xF0\x9E\x0E\x10\x50", "xx????x", anAddressWithinFpslimitCommand, sizeOfImage - anAddressWithinFpslimitCommand) - 0x4;
            if (cchatRefAddressStart + 0x4)
            {
                size_t cchatRefAddress = *reinterpret_cast<size_t*>(cchatRefAddressStart);
                cchat_unofficial::SetCChatRef(cchatRefAddress);

                unsigned long anAddressWithinAddMessage = mem_find_pattern("\x2B\xC2\x3D\x90\x00\x00\x00\x77", "xxxxxxxx", baseAddress, sizeOfImage);
                if (anAddressWithinAddMessage)
                {
                    unsigned long addMessageAddress = mem_find_pattern_backwards_starting_at("\x56", "x", baseAddress, anAddressWithinAddMessage);
                    if (addMessageAddress)
                    {
                        cchat_unofficial::SetAddMessageAddress(addMessageAddress);
                    }
                }
            }
        }
    }

    static void RemoveSampLimits()
    {
        GetBase();
        if (!baseAddress)
        {
            return;
        }

        DWORD old_prot;

        unsigned long sampProcessFrameLimiterCaller = mem_find_pattern("\x89\x65\xE8\x8B\x0D\xAC\xEB\x26\x10\x85\xC9\x74\x05\xE8", "xxxxx????xxxxx", baseAddress, sizeOfImage) + 0x3;
        if (sampProcessFrameLimiterCaller - 0x3 && VirtualProtect((void*)sampProcessFrameLimiterCaller, 15, PAGE_EXECUTE_READWRITE, &old_prot))
        {
            DWORD new_prot = old_prot;
            memset(reinterpret_cast<void*>(sampProcessFrameLimiterCaller), 0x90, 15);
            VirtualProtect((void*)sampProcessFrameLimiterCaller, 15, new_prot, &old_prot);
        }

        unsigned long hardcodedSleep1 = mem_find_pattern("\xBA\x80\x1A\x56\x00\xFF\xE2", "xxxxxxx", baseAddress, sizeOfImage) - 0x7;
        if (hardcodedSleep1 + 0x7 && VirtualProtect((void*)hardcodedSleep1, 1, PAGE_EXECUTE_READWRITE, &old_prot))
        {
            DWORD new_prot = old_prot;
            mem_put<unsigned char>(hardcodedSleep1, 0x0);
            VirtualProtect((void*)hardcodedSleep1, 1, new_prot, &old_prot);
        }
    }
};
