#pragma once
#include <plugin.h>

#include <Detours/detours.h>

namespace renderware_hook
{
    using PRwD3D9EngineSetRefreshRate = decltype(RwD3D9EngineSetRefreshRate)*;
	PRwD3D9EngineSetRefreshRate originalRwD3D9EngineSetRefreshRate = nullptr;

	void hkRwD3D9EngineSetRefreshRate(RwUInt32 refreshRate)
	{
		RwUInt32 newRefreshRate = 60;
		HWND hwnd = GetForegroundWindow();
		// get current display from window
		HMONITOR hMonitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
		if (hMonitor)
		{
			MONITORINFOEX mi;
			mi.cbSize = sizeof(MONITORINFOEX);

			// get display info
			if (GetMonitorInfo(hMonitor, &mi))
			{
				DEVMODE devMode;
				devMode.dmSize = sizeof(DEVMODE);
				if (EnumDisplaySettings(mi.szDevice, ENUM_CURRENT_SETTINGS, &devMode))
				{
					// get refresh rate (HZ)
					refreshRate = devMode.dmDisplayFrequency;
				}
			}
		}

		originalRwD3D9EngineSetRefreshRate(refreshRate); // update refresh rate
	};

	void ReplaceRwSetRefreshRate()
	{
		originalRwD3D9EngineSetRefreshRate = (PRwD3D9EngineSetRefreshRate)DetourFunction((PBYTE)0x7F8580, (PBYTE)hkRwD3D9EngineSetRefreshRate);
	}
};
