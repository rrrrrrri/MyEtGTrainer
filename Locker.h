#pragma once
#include <iostream>
#include <Windows.h>


class Locker
{
private:
	BOOL bHealthLock;
	BOOL bArmorLock;
	BOOL bBlankLock;
	BOOL bInfAmmoLock;
	BOOL bOneShotKillLock;
public:
	Locker() { bHealthLock = false; bArmorLock = false; bBlankLock = false; bInfAmmoLock = false; bOneShotKillLock = false; }
	~Locker() {}
	
	BOOL GetHealthLock();
	BOOL GetArmorLock();
	BOOL GetBlankLock();
	BOOL GetInfAmmoLock();
	BOOL GetOneShotKillLock();
	void SetHealthLock(BOOL newLock);
	void SetArmorLock(BOOL newLock);
	void SetBlankLock(BOOL newLock);
	void SetInfAmmoLock(BOOL newLock);
	void SetOneShotKillLock(BOOL newLock);

	void update();

};

