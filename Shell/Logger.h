#pragma once
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

#include <string>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <typeinfo>
#include <source_location>
#include <fstream>
#include <windows.h>
#include <queue>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

class Logger
{
public:
	Logger() { };

	void print(string msg, const std::source_location& caller = std::source_location::current());

	~Logger() { };

private:
	string getCurrentTimeLogFormatted();
	string getCurrentTimeFileFormatted();
	string extractCallerName(const char* funcSig);
	string formatCallFunction(string callFunction);
	long long getFileSize(const std::string& filename);
	string getSaveFileName();
	bool changeFileName(string from, string to);
	void writeToLogFile(string contents);
	void agingLogFile();
	void doZip();

	const string LOGFILE = "latest.log";
	const long long TEN_KB = 10240;
	queue<string> logFileQueue;
};