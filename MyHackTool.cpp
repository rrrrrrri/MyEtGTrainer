// MyHackTool.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "stdafx.h"
#include "Proc.h"
#include "mem.h"

void banner(BOOL healthLock, BOOL armorLock) {
    system("cls");
    std::cout << "[挺进地牢]修改器 [v0.1]" << std::endl;
    std::cout << "======================" << std::endl;
    if (healthLock) {
        std::cout << "生命值锁定  ->  True" << std::endl;
    }
    else {
        std::cout << "生命值锁定  ->  False" << std::endl;
    }
    if (armorLock) {
        std::cout << "护甲锁定  ->  True" << std::endl;
    }
    else {
        std::cout << "护甲锁定  ->  False" << std::endl;
    }
}

int main()
{
    Proc processTool;
    mem memTool;
    BOOL healthLock = false, armorLock = false;
    DWORD procId = processTool.GetProcessID(L"EtG.exe");
    if (procId == 0) {
        std::cout << "找不到指定进程！" << std::endl;
        return 0;
    }
    std::cout << "成功找到 Game 进程  ->  " << procId << std::endl;
    uintptr_t modBase = processTool.GetModuleBaseAddress(procId, L"UnityPlayer.dll");
    if (modBase == 0) {
        std::cout << "无法定位模块基址！" << std::endl;
        return 0;
    }
    std::cout << "成功定位模块基址  ->  " << std::endl;
    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
    if (hProc == INVALID_HANDLE_VALUE) {
        std::cout << "无法附加到进程！" << std::endl;
        return 0;
    }
    uintptr_t PlayerStaticPointer = modBase + 0x144ebb8;
    std::vector <unsigned int> healthOffsets = { 0x8, 0x98, 0x28, 0x30, 0x18, 0x50, 0x118 };
    std::vector <unsigned int> armorOffsets = { 0x8, 0x98, 0x28, 0x30, 0x18, 0x50, 0x11c };
    std::cout << "\n\n" << std::endl;
    banner(healthLock, armorLock);
    DWORD dwExit = 0;

    while (GetExitCodeProcess(hProc, &dwExit) && dwExit == STILL_ACTIVE) {   // 进程没有退出
        if (GetAsyncKeyState(VK_NUMPAD0) & 1) {
            healthLock = !healthLock;    // 开启生命值锁定
            banner(healthLock, armorLock);
        }
        if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
            armorLock = !armorLock;
            banner(healthLock, armorLock);
        }
        if (GetAsyncKeyState(VK_NUMPAD2) & 1) {
            std::cout << "Exit!" << std::endl;
            return 0;
        }
        if (healthLock) {    // 如果生命值锁定开启
            uintptr_t healthDynPtr = processTool.GetDMAAddress(hProc, PlayerStaticPointer, healthOffsets);    // 读取动态数据地址
            float health = 0;
            ReadProcessMemory(hProc, (BYTE*)healthDynPtr, &health, sizeof(health), nullptr);    // 读取生命值
            //std::cout << "Current health: " << health << std::endl;
            if (health == 0) {     // 生命值为 0 则跳过，防止发生异常
                continue;
            }
            health = 3;
            WriteProcessMemory(hProc, (BYTE*)healthDynPtr, &health, sizeof(health), nullptr);
            //std::cout << "Changed health to 3" << std::endl;
            Sleep(10);    // sleep 10 毫秒
        }
        if (armorLock) {
            uintptr_t armorDynptr = processTool.GetDMAAddress(hProc, PlayerStaticPointer, armorOffsets);
            float armor = 0;
            ReadProcessMemory(hProc, (BYTE*)armorDynptr, &armor, sizeof(armor), nullptr);  // 读取护甲
            armor = 5;
            WriteProcessMemory(hProc, (BYTE*)armorDynptr, &armor, sizeof(armor), nullptr);
            Sleep(10);
        }
    }
}
