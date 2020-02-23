#pragma once
#include <Windows.h>
#include <fstream>

class Injector
{
public:
	bool injectTo(HANDLE hProc, char* DllFile);
};

