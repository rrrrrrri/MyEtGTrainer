#pragma once
#include "stdafx.h"

class Proc
{
public:
	DWORD GetProcessID(const wchar_t* procName);  // ��ȡ process ID
	uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName);    // ��ȡģ���ַ
	uintptr_t GetDMAAddress(HANDLE hProc, uintptr_t ptr, std::vector <unsigned int> offsets);   // ��ȡ��̬���ݵ�ַ

	Proc() {}
	~Proc() {}
};

