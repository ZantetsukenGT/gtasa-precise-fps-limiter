#pragma once
#include "pch.h"
#include "util.h"

namespace renderware_hook
{
    using t_t = decltype(RwD3D9EngineSetRefreshRate)*;
    t_t oRwD3D9EngineSetRefreshRate = nullptr;


	void hkRwD3D9EngineSetRefreshRate(RwUInt32 refreshRate)
	{
		RwVideoMode videomode;
		RwUInt32 index = RwEngineGetCurrentVideoMode();
		RwEngineGetVideoModeInfo(&videomode, index);
		oRwD3D9EngineSetRefreshRate(videomode.refRate);
	};

	void ReplaceRwSetRefreshRate()
	{
		oRwD3D9EngineSetRefreshRate = (t_t)DetourFunction((PBYTE)0x7F8580, (PBYTE)hkRwD3D9EngineSetRefreshRate);
	}
};

