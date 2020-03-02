#pragma once
#include "stdafx.h"

class Proc
{
public:
	DWORD GetProcessID(const wchar_t* procName);  // 获取 process ID
	uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName);    // 获取模块基址
	uintptr_t GetDMAAddress(HANDLE hProc, uintptr_t ptr, std::vector <unsigned int> offsets);   // 获取动态数据地址

	Proc() {}
	~Proc() {}
};

