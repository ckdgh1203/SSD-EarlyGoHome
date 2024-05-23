#pragma once
#include <string>
#include <Windows.h>

using namespace std;

class ISsdExecutable
{
public:
    virtual bool execute(const string& arguments) = 0;
private:

};

class SsdExecutable : public ISsdExecutable
{
public:
    SsdExecutable()
    {
        
    }

    bool execute(const string& arguments) override
    {
        string command = std::string(ssdExcutablePath) + " " + arguments;
        STARTUPINFOA si{};
        PROCESS_INFORMATION pi{};

        if (!CreateProcessA(
            nullptr,
            const_cast<char*>(command.c_str()),
            nullptr,
            nullptr,
            FALSE,
            0,
            nullptr,
            nullptr,
            &si,
            &pi)
        )
        {
            return false;
        }

        WaitForSingleObject(pi.hProcess, INFINITE);

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        return true;
    }
private:
    const char* ssdExcutablePath = "SSD.exe";
};
