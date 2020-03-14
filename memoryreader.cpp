#include "memoryreader.h"

MemoryReader::MemoryReader()
{

}

bool MemoryReader::openProcess(DWORD pid)
{
    pHandle = OpenProcess(PROCESS_ALL_ACCESS, 0,  pid);
    if (pHandle == nullptr)
        return false;
    else
        return  true;
}

void MemoryReader::closeProcess()
{
    CloseHandle(pHandle);
}

int MemoryReader::readInt(uintptr_t address, int defaultValue)
{
    int value;
    SIZE_T totalRead;

    if (pHandle == nullptr)
        return defaultValue;

    ReadProcessMemory(pHandle, (LPVOID)address, (LPVOID)(&value), sizeof(int), &totalRead);
    return value;
}

uintptr_t MemoryReader::getModuleBaseAddress(DWORD procId, const wchar_t* modName)
{
    uintptr_t modBaseAddr = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
    if (hSnap != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32 modEntry;
        modEntry.dwSize = sizeof(modEntry);
        if (Module32First(hSnap, &modEntry))
        {
            do
            {
                if (!_wcsicmp(modEntry.szModule, modName))
                {
                    modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                    break;
                }
            } while (Module32Next(hSnap, &modEntry));
        }
    }
    CloseHandle(hSnap);
    return modBaseAddr;
}
