#pragma once
#include <Windows.h>
#include "Player.h"

class Cheate
{
private:
	Player internalPlayer;
	HANDLE hProc;
public:
	Cheate(Player newPlayer, HANDLE newhProc) { 
		internalPlayer = newPlayer; 
		hProc = newhProc;
	}
	~Cheate() {}
	
	BOOL LockHealth();
	BOOL LockArmor();
};

