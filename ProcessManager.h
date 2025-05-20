#pragma once
#include <windows.h>
#include <vector>
#include <string>

class ProcessManager {
public:
    static DWORD FindProcess(const std::string& name);
    static HANDLE Attach(DWORD pid);
    static std::vector<uint8_t> DumpMemory(HANDLE hProcess, uintptr_t address, size_t size);
    static std::vector<std::string> ListInstalledTools();  // Поиск инструментов
};