#include "pch.h"
#include "memory.h"

unsigned long mem_find_pattern(const char* pattern, const char* mask, unsigned long base_address, unsigned long size_of_image)
{
	unsigned long pattern_len = (unsigned long)strlen(mask);

	for (unsigned long i = 0; i != size_of_image - pattern_len; ++i)
	{
		bool found = true;

		for (unsigned long j = 0; j != pattern_len; ++j)
		{
			found &= mask[j] == '?' || pattern[j] == *(char*)(base_address + i + j);
		}

		if (found)
		{
			return base_address + i;
		}
	}

	return 0;
}

void _patch(void* addr, void* data, int size)
{
	unsigned long prot[2]{};
	VirtualProtect(addr, size, PAGE_EXECUTE_READWRITE, &prot[0]);

	memcpy(addr, data, size);
}

void _nop(void* addr, int size)
{
	unsigned long prot[2]{};
	VirtualProtect(addr, size, PAGE_EXECUTE_READWRITE, &prot[0]);

	memset(addr, 0x90, size);

	VirtualProtect(addr, size, prot[0], &prot[1]);
}

bool check(void* addr, unsigned char byte, bool _continue)
{
	if (_check(addr, byte))
	{
		return true;
	}

	if (_continue)
	{
		return false;
	}

	return false;
}

bool _check(void* addr, unsigned char byte)
{
	unsigned long prot[2]{};
	unsigned char val = byte;

	VirtualProtect(addr, 1, PAGE_EXECUTE_READ, &prot[0]);

	memcpy(&val, addr, 1);

	VirtualProtect(addr, 1, prot[0], &prot[1]);
	return val == byte;
}