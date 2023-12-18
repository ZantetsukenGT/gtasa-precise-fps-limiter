#pragma once

#define patch(a, v, s) _patch((void*)(a), (void*)(v), (s))
#define nop(a, s) _nop((void*)(a), (s))

unsigned long mem_find_pattern(const char* pattern, const char* mask, unsigned long base_address, unsigned long size_of_image);
void _patch(void*, void*, int);
void _nop(void*, int);
bool check(void*, unsigned char, bool);
bool _check(void*, unsigned char);

template <class T>
inline void mem_put_s(int ptr, const T value, int size = sizeof(T))
{
	void* ptr_ = reinterpret_cast<void*>(ptr);

	if (*(static_cast<T*>(ptr_)) != value)
	{
		memcpy(ptr_, &value, size);
	}
}

template<class T, class U>
inline void mem_put(U ptr, const T value)
{
	if (*(T*)ptr != value)
	{
		memcpy((void*)ptr, &value, sizeof(T));
	}
}

template<class T, class U>
inline void mem_put_fast(U ptr, const T value)
{
	*(T*)ptr = value;
}