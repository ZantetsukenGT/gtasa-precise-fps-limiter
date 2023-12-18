#pragma once
#include "pch.h"

inline void enable_console()
{
    AllocConsole();

    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
}

inline void dbg(const char* fmt, ...)
{
    va_list argp;
    va_start(argp, fmt);

    char dbg_out[422];
    vsprintf_s(dbg_out, fmt, argp);

    va_end(argp);

    // Even if the console isn't enabled we can still debug
    OutputDebugStringA(dbg_out);
    printf("%s\n", dbg_out);
}
