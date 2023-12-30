#pragma once
#include "pch.h"
#include "util.h"

namespace cchat_unofficial
{
	using lmao = void(__thiscall*)(void*, D3DCOLOR, const char*);

	void* GetRefR2()
	{
		return *(void**)sampapi::GetAddress(0x21A0EC);
	}

	void* GetRefR4()
	{
		return *(void**)sampapi::GetAddress(0x26E9F8);
	}

	void* GetRefDL()
	{
		return *(void**)sampapi::GetAddress(0x2ACA10);
	}

	void AddMessageR2(D3DCOLOR prefixColor, const char* szText)
	{
		((lmao)sampapi::GetAddress(0x64670))(GetRefR2(), prefixColor, szText);
	}

	void AddMessageR4(D3DCOLOR prefixColor, const char* szText)
	{
		((lmao)sampapi::GetAddress(0x68130))(GetRefR4(), prefixColor, szText);
	}

	void AddMessageDL(D3DCOLOR prefixColor, const char* szText)
	{
		((lmao)sampapi::GetAddress(0x67BE0))(GetRefDL(), prefixColor, szText);
	}
};
