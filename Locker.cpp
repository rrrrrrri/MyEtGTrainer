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
	std::cout << "[ͦ������]�޸��� [v0.2]" << std::endl;
	std::cout << "======================" << std::endl;
	std::cout << "����ֵ����  ->  " << bHealthLock << std::endl;
	std::cout << "��������  ->  " << bArmorLock << std::endl;
	std::cout << "���쵯���� -> " << bBlankLock << std::endl;
	std::cout << "�����ӵ� -> " << bInfAmmoLock << std::endl;
	std::cout << "һ����ɱ -> " << bOneShotKillLock << std::endl;

}