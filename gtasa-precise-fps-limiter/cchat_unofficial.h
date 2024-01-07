#pragma once
#include "pch.h"
#include "util.h"

namespace cchat_unofficial
{
	using lmao = void(__thiscall*)(void*, D3DCOLOR, const char*);

	static DWORD CChatAddress = 0;
	static DWORD AddMessageAddress = 0;

	inline void SetCChatRef(DWORD cchatAddress)
	{
		CChatAddress = cchatAddress;
	}

	inline void SetAddMessageAddress(DWORD addMessageAddress)
	{
		AddMessageAddress = addMessageAddress;
	}

	inline void AddMessage(D3DCOLOR prefixColor, const char* szText)
	{
		if (AddMessageAddress && CChatAddress)
		{
			((lmao)AddMessageAddress)(*(void**)CChatAddress, prefixColor, szText);
		}
	}
};
