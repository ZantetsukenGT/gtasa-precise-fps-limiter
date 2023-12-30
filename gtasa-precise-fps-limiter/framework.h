#pragma once

//#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <chrono>
#include <plugin.h>
#include <d3d9.h>

// comentar si queremos usar el limiter moderno
#define WIN8_1_AND_LOWER_COMPAT
#ifndef WIN8_1_AND_LOWER_COMPAT
#pragma comment(lib, "ntdll.lib")
#endif
#pragma comment(lib, "winmm.lib")

#include <detours.h>
#include <sampapi/CChat.h>
#include <sampapi/CGame.h>
#include <sampapi/CNetGame.h>
#include <sampapi/Commands.h>

#include "common_types.h"

