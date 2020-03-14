#ifndef MEMORYREADER_H
#define MEMORYREADER_H

#include <windows.h>
#include <TlHelp32.h>
#include <string>

class MemoryReader
{
public:
    MemoryReader();
    bool openProcess(DWORD pid);
    void closeProcess();
    int readInt(uintptr_t address, int defaultValue=0);
    uintptr_t getModuleBaseAddress(DWORD procId, const wchar_t* modName);

private:
    HANDLE pHandle;
};

#endif // MEMORYREADER_H
