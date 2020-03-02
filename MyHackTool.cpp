// MyHackTool.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "stdafx.h"
#include "Proc.h"
#include "Locker.h"
#include "mem.h"
#include "Player.h"

int main()
{
    Locker lock;
    Proc processTool;
    mem memTool;
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
    
    Player* player = new Player(hProc, PlayerStaticPointer);
    lock.update();
    DWORD dwExit = 0;
    uintptr_t currentGun = 0;

    while (GetExitCodeProcess(hProc, &dwExit) && dwExit == STILL_ACTIVE) {   // 进程没有退出
        if (GetAsyncKeyState(VK_NUMPAD0) & 1) {
            lock.SetHealthLock(!lock.GetHealthLock());    // 开启生命值锁定
            lock.update();
        }
        if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
            lock.SetArmorLock(!lock.GetArmorLock());
            lock.update();
        }
        if (GetAsyncKeyState(VK_NUMPAD2) & 1) {
            lock.SetBlankLock(!lock.GetBlankLock());
            lock.update();
        }
        if (GetAsyncKeyState(VK_NUMPAD3) & 1) {
            lock.SetInfAmmoLock(!lock.GetInfAmmoLock());
            //currentGun = player->GetCurrentGun();
            player->SetInfAmmo(lock.GetInfAmmoLock());
            lock.update();
        }
        if (GetAsyncKeyState(VK_NUMPAD4) & 1) {
            lock.SetOneShotKillLock(!lock.GetOneShotKillLock());
            player->SetOneShotKill(lock.GetOneShotKillLock());
            lock.update();
        }
        if (GetAsyncKeyState(VK_NUMPAD5) & 1) {
            std::cout << "Exit!" << std::endl;
            return 0;
        }
        if (lock.GetHealthLock()) {    // 如果生命值锁定开启
            float health = player->GetHealth();
            if (health == 0) {
                continue;
            }
            health = 3;
            player->SetHealth(health);
            Sleep(10);    // sleep 10 毫秒
        }
        if (lock.GetArmorLock()) {
            float armor = player->GetArmor();
            armor = 5;
            player->SetArmor(armor);
            Sleep(10);
        }
        if (lock.GetBlankLock()) {
            DWORD blank = player->GetBlank();
            blank = 5;
            player->SetBlank(blank);
            Sleep(10);
        }
    }
}
