#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
#include "Proc.h"

class Player
{
private:
	uintptr_t basePointer;
	float health;
	float armor;
	DWORD blank;
	Proc processTool;
	uintptr_t currentGun;

	HANDLE hProc;
public:
	std::vector <unsigned int> healthOffsets = { 0x8, 0x98, 0x28, 0x30, 0x18, 0x50, 0x118 };  // float
	std::vector <unsigned int> armorOffsets = { 0x8, 0x98, 0x28, 0x30, 0x18, 0x50, 0x11c };   // float
	std::vector <unsigned int> blankOffsets = { 0x8, 0x98, 0x28, 0x30, 0x568 };               // int
	std::vector <unsigned int> infAmmoOffsets = { 0x8, 0x98, 0x28, 0x30, 0x278, 0x28, 0x3b5 }; // bool
	std::vector <unsigned int> oneShotKillOffsets = { 0x8, 0x98, 0x28, 0x30, 0x278, 0x28, 0x3e7 };  // int
	std::vector <unsigned int> currentGunOffsets = { 0x8, 0x98, 0x28, 0x30, 0x278, 0x28 };  // int

	float GetHealth();
	float GetArmor();
	DWORD GetBlank();
	uintptr_t GetCurrentGun();
	void SetHealth(float newHealth);
	void SetArmor(float newArmor);
	void SetBlank(DWORD newBlank);
	void SetInfAmmo(BOOL ammoLock);
	void SetOneShotKill(BOOL oneShotKillLock);


	Player(HANDLE Proc, uintptr_t base) { hProc = Proc; basePointer = base; }
};

