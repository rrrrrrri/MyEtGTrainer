#include "stdafx.h"
#include "Proc.h"

DWORD Proc::GetProcessID(const wchar_t* procName){
	DWORD procId = 0;

	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32 procEntry = { sizeof(procEntry) };
		if (Process32First(hSnap, &procEntry)) {
			do
			{
				if (!_wcsicmp(procEntry.szExeFile, procName)) {
					procId = procEntry.th32ProcessID;
					break;
				}

			} while (Process32Next(hSnap, &procEntry));
		}
	}
	CloseHandle(hSnap);
	return procId;
}
uintptr_t Proc::GetModuleBaseAddress(DWORD procId, const wchar_t* modName) {
	uintptr_t modBase = 0;

	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
	if (hSnap != INVALID_HANDLE_VALUE) {
		MODULEENTRY32 modEntry = { sizeof(modEntry) };
		if (Module32First(hSnap, &modEntry)) {
			do
			{
				if (!_wcsicmp(modEntry.szModule, modName)) {
					modBase = (uintptr_t)modEntry.modBaseAddr;
					break;
				}

			} while (Module32Next(hSnap, &modEntry));
		}
	}
	CloseHandle(hSnap);
	return modBase;
}
uintptr_t Proc::GetDMAAddress(HANDLE hProc, uintptr_t ptr, std::vector <unsigned int> offsets) {
	uintptr_t dma = 0;
	dma = ptr;
	for (int i = 0; i < offsets.size(); i++) {
		ReadProcessMemory(hProc, (BYTE*)dma, &dma, sizeof(dma), nullptr);
		dma += offsets[i];
	}
	return dma;
}
