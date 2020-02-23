#include "mem.h"

void mem::PatchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProc) {
	DWORD oldProtect;
	VirtualProtectEx(hProc, dst, size, PAGE_EXECUTE_READWRITE, &oldProtect);
	WriteProcessMemory(hProc, dst, src, size, nullptr);
	VirtualProtectEx(hProc, dst, size, oldProtect, &oldProtect);
}

void mem::NopEx(BYTE* dst, unsigned int size, HANDLE hProc) {
	BYTE* nopArr = new BYTE[size];
	memset(nopArr, 0x90, size);
	PatchEx(dst, nopArr, size, hProc);
	delete[] nopArr;
}

bool isMemMatchFeature(BYTE* mem, BYTE* feature, BYTE* mask) {
	int featureLen = strlen((char*)feature);

	for (int i = 0; i < featureLen; i++) {
		if (mask[i] == 'x' && mem[i] != feature[i]) {
			return false;
		}
	}
	return true;
}

uintptr_t mem::SearchPattern(HANDLE hProc, uintptr_t modBase, unsigned int size, BYTE* feature, BYTE* mask) {
	// 1. 遍历目标内存，每次取出 len(feature) 长度的字节
	// 2. 判断取出的字节对应位置和 feature 
	// 3. 如果 mask 对应位置为 x，则两者应该相等，否则可以跳过
	if (hProc == 0) {
		return 0;
	}

	unsigned int i = 0;
	unsigned int featureLen = strlen((char*)feature);
	BYTE* tempArr = new BYTE[featureLen];

	while (i < size) {
		ReadProcessMemory(hProc, (BYTE*)modBase, tempArr, featureLen, nullptr);
		if (isMemMatchFeature(tempArr, feature, mask)) {
			return modBase;
		}
		else {
			modBase += 1;
		}
	}
	return 0;
	
}
