#include "Injector.h"
#include <Windows.h>

bool Injector::injectTo(HANDLE hProc, char* DllFile) {
	if (hProc == 0) {
		return false;
	}
	LPVOID injectMem = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (injectMem == 0) {
		return false;
	}
	unsigned int dllFileNameLen = strlen(DllFile);
	WriteProcessMemory(hProc, injectMem, &DllFile, dllFileNameLen, nullptr);
	HANDLE hrProcess = CreateRemoteThread(hProc, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibrary, injectMem, NULL, 0);
	if (hrProcess == 0) {
		return false;
	}
	CloseHandle(hrProcess);
	return true;
}
