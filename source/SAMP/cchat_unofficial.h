#pragma once

#include <d3d9.h>

namespace cchat_unofficial
{
	using PAddMessageAddress = void(__thiscall*)(void*, D3DCOLOR, const char*);

	static size_t CChatAddress = 0;
	static size_t AddMessageAddress = 0;

	inline void SetCChatRef(size_t cchatAddress)
	{
		CChatAddress = cchatAddress;
	}

	inline void SetAddMessageAddress(size_t addMessageAddress)
	{
		AddMessageAddress = addMessageAddress;
	}

	inline void AddMessage(D3DCOLOR prefixColor, const char* szText)
	{
		if (AddMessageAddress && CChatAddress)
		{
			reinterpret_cast<PAddMessageAddress>(AddMessageAddress)(*reinterpret_cast<void**>(CChatAddress), prefixColor, szText);
		}
	}
};
