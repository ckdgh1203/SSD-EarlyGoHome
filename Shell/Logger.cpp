#pragma once
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

#include <string>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <typeinfo>
#include <source_location>

using namespace std;

class Logger
{
public:
    Logger()
    {
         latest = new FILE();
    };

    void print(string msg, const std::source_location& loc = std::source_location::current())
    {
        string buf(30, ' ');
        string callFunction = extractClassName(loc.function_name());
        formattingCallFunction(buf, callFunction);
        cout << "[" << getCurrentTimeFormatted() << "] " << buf << " : " << msg << endl;
    }

    void getNextFile()
    {
        cout << "Get Next File " << endl;
    }

    void zip()
    {
        cout << "Zip " << endl;
    }

    ~Logger()
    {
        if (latest)
            fclose(latest);
    };
private:
    string getCurrentTimeFormatted()
    {
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        std::stringstream ss;
        ss << std::put_time(std::localtime(&now), "%y.%m.%d %H:%M");

        std::string formattedTime = ss.str();

        return ss.str();
    }

    string extractClassName(const char* funcSig)
    {
        std::string sig(funcSig);
        size_t start = sig.find(" ") + 1;
        start = sig.find(" ", start) + 1;
        size_t end = sig.find("::", start);
        return sig.substr(start, end - start);
    }

    string formattingCallFunction(string &buf, string callFunction)
    {
        int length = callFunction.size();
        if (length > 30)
            callFunction.resize(30);
        buf.replace(0, length, callFunction);
        return buf;
    }

    FILE* latest;
};