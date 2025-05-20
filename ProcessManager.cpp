#include "ProcessManager.h"
#include <tlhelp32.h>
#include <filesystem>

DWORD ProcessUtils::FindProcess(const std::string& name) {
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (Process32First(hSnapshot, &pe32)) {
        do {
            if (name == pe32.szExeFile) {
                CloseHandle(hSnapshot);
                return pe32.th32ProcessID;
            }
        } while (Process32Next(hSnapshot, &pe32));
    }
    CloseHandle(hSnapshot);
    return 0;
}

HANDLE ProcessUtils::Attach(DWORD pid) {
    return OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
}

std::vector<uint8_t> ProcessUtils::DumpMemory(HANDLE hProcess, uintptr_t address, size_t size) {
    std::vector<uint8_t> buffer(size);
    SIZE_T bytesRead;
    ReadProcessMemory(hProcess, (LPCVOID)address, buffer.data(), size, &bytesRead);
    return buffer;
}

bool ProcessUtils::SaveToFile(const std::string& path, const std::vector<uint8_t>& data) {
    FILE* file = fopen(path.c_str(), "wb");
    if (!file) return false;
    fwrite(data.data(), 1, data.size(), file);
    fclose(file);
    return true;
}

std::vector<std::string> ProcessManager::ListInstalledTools() {
    std::vector<std::string> tools;

    // Проверяем наличие инструментов в стандартных путях
    if (std::filesystem::exists("C:\\Program Files\\Cheat Engine 7.4\\cheatengine-x86_64.exe")) {
        tools.push_back("Cheat Engine 7.4");
    }
    if (std::filesystem::exists("C:\\Program Files\\IDA Pro 8.3\\ida64.exe")) {
        tools.push_back("IDA Pro 8.3");
    }

    return tools;
}