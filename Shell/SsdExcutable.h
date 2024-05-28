#pragma once
#include <string>
#include <Windows.h>
#include <tchar.h>
#include <fstream>
#include <iostream>

using namespace std;

class ISsdExecutable
{
public:
    virtual bool execute(const string& arguments) = 0;
    virtual string getResultFilePath() = 0;
private:
};

class SsdExecutable : public ISsdExecutable
{
public:
    SsdExecutable() { }

    bool execute(const string& arguments) override
    {
        bool needFileHandle = arguments == "G" ? true : false;
        string command = std::string(ssdExcutablePath) + " " + arguments;

        PROCESS_INFORMATION pi{};
        STARTUPINFOA si{};
        HANDLE h = needFileHandle ? getResultFileHandle() : NULL;

        initProcessInfo(pi, si, h);

        if (!CreateProcessA(
            nullptr,
            const_cast<char*>(command.c_str()),
            nullptr,
            nullptr,
            needFileHandle,
            CREATE_NO_WINDOW,
            nullptr,
            nullptr,
            &si,
            &pi)
        )
        {
            return false;
        }

        WaitForSingleObject(pi.hProcess, INFINITE);
        
        if (needFileHandle)
            CloseHandle(h);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        return true;
    }

    string getResultFilePath()
    {
        string resultFilePath;

        ifstream redirectFile(redirectPath);

        if (!redirectFile.is_open())
        {
            return "";
        }

        string line;
        while (getline(redirectFile, line))
        {
            resultFilePath = line;
        }

        redirectFile.close();
        if (remove(redirectPath) != 0)
            return "";

        return resultFilePath;
    }

private:
    HANDLE getResultFileHandle()
    {
        SECURITY_ATTRIBUTES sa;
        sa.nLength = sizeof(sa);
        sa.lpSecurityDescriptor = NULL;
        sa.bInheritHandle = TRUE;
        HANDLE h = CreateFileA(redirectPath,
            FILE_GENERIC_WRITE,
            FILE_SHARE_WRITE,
            &sa,
            CREATE_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            NULL);

        return h;
    }

    void initProcessInfo(PROCESS_INFORMATION& pi, STARTUPINFOA& si, HANDLE h)
    {
        ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
        ZeroMemory(&si, sizeof(STARTUPINFO));
        si.cb = sizeof(STARTUPINFO);
        si.dwFlags |= STARTF_USESTDHANDLES;
        si.hStdInput = NULL;
        si.hStdError = h;
        si.hStdOutput = h;
    }

    const char* ssdExcutablePath = "SSD.exe";
    const char* redirectPath = ".redirect.tmp";
};
