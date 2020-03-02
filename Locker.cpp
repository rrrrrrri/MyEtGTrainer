#include "Locker.h"
#include <Windows.h>
#include <iostream>

BOOL Locker::GetHealthLock() {
	return bHealthLock;
}
BOOL Locker::GetArmorLock() {
	return bArmorLock;
}
BOOL Locker::GetBlankLock() {
	return bBlankLock;
}
BOOL Locker::GetInfAmmoLock() {
	return bInfAmmoLock;
}
BOOL Locker::GetOneShotKillLock() {
	return bOneShotKillLock;
}

void Locker::SetHealthLock(BOOL newLock) {
	bHealthLock = newLock;
}
void Locker::SetArmorLock(BOOL newLock) {
	bArmorLock = newLock;
}
void Locker::SetBlankLock(BOOL newLock) {
	bBlankLock = newLock;
}
void Locker::SetInfAmmoLock(BOOL newLock) {
	bInfAmmoLock = newLock;
}
void Locker::SetOneShotKillLock(BOOL newLock) {
	bOneShotKillLock = newLock;
}

void Locker::update() {
	system("cls");
	std::cout << "[挺进地牢]修改器 [v0.2]" << std::endl;
	std::cout << "======================" << std::endl;
	std::cout << "生命值锁定  ->  " << bHealthLock << std::endl;
	std::cout << "护甲锁定  ->  " << bArmorLock << std::endl;
	std::cout << "空响弹锁定 -> " << bBlankLock << std::endl;
	std::cout << "无限子弹 -> " << bInfAmmoLock << std::endl;
	std::cout << "一击必杀 -> " << bOneShotKillLock << std::endl;

}