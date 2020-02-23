#pragma once
#include"stdafx.h"

class mem
{
public:
	void PatchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProc);
	void NopEx(BYTE* dst, unsigned int size, HANDLE hProc);
	uintptr_t SearchPattern(HANDLE hProc, uintptr_t modBase, unsigned int size, BYTE* feature, BYTE* mask);

	mem() {}
	~mem() {}
};

