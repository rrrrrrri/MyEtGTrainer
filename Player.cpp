#include "Player.h"
#include <Windows.h>
#include <vector>
#include "Proc.h"

float Player::GetHealth() {
	health = 0;
	uintptr_t healthPtr = processTool.GetDMAAddress(hProc, basePointer, healthOffsets);
	ReadProcessMemory(hProc, (BYTE*)healthPtr, &health, sizeof(health), nullptr);
	return health;
}
float Player::GetArmor() {
	armor = 0;
	uintptr_t armorPtr = processTool.GetDMAAddress(hProc, basePointer, armorOffsets);
	ReadProcessMemory(hProc, (BYTE*)armorPtr, &armor, sizeof(armor), nullptr);
	return armor;
}
DWORD Player::GetBlank() {
	blank = 0;
	uintptr_t blankPtr = processTool.GetDMAAddress(hProc, basePointer, blankOffsets);
	ReadProcessMemory(hProc, (BYTE*)blankPtr, &blank, sizeof(blank), nullptr);
	return blank;
}
uintptr_t Player::GetCurrentGun() {
	uintptr_t gunPtr = processTool.GetDMAAddress(hProc, basePointer, currentGunOffsets);
	ReadProcessMemory(hProc, (BYTE*)gunPtr, &currentGun, sizeof(currentGun), nullptr);
	return currentGun;
}

void Player::SetHealth(float newHealth) {
	health = newHealth;
	uintptr_t healthPtr = processTool.GetDMAAddress(hProc, basePointer, healthOffsets);
	WriteProcessMemory(hProc, (BYTE*)healthPtr, &health, sizeof(health), nullptr);
}
void Player::SetArmor(float newArmor) {
	armor = newArmor;
	uintptr_t armorPtr = processTool.GetDMAAddress(hProc, basePointer, armorOffsets);
	WriteProcessMemory(hProc, (BYTE*)armorPtr, &armor, sizeof(armor), nullptr);
}
void Player::SetBlank(DWORD newBlank) {
	blank = newBlank;
	uintptr_t blankPtr = processTool.GetDMAAddress(hProc, basePointer, blankOffsets);
	WriteProcessMemory(hProc, (BYTE*)blankPtr, &blank, sizeof(blank), nullptr);
}
void Player::SetInfAmmo(BOOL ammoLock) {
	BYTE s = 0;
	uintptr_t infAmmoPtr = processTool.GetDMAAddress(hProc, basePointer, infAmmoOffsets);
	if (ammoLock) {
		BYTE s = 1;
	}
	WriteProcessMemory(hProc, (BYTE*)infAmmoPtr, &s, sizeof(s), nullptr);
}
void Player::SetOneShotKill(BOOL oneShotKillLock) {
	DWORD s = 0;
	if (oneShotKillLock) {
		s = 0x00020202;
	}
	uintptr_t gunDamagePtr = processTool.GetDMAAddress(hProc, basePointer, oneShotKillOffsets);
	WriteProcessMemory(hProc, (BYTE*)gunDamagePtr, &s, sizeof(s), nullptr);
}
