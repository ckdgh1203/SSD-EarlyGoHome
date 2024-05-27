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

	void print(string msg, const std::source_location& caller = std::source_location::current())
	{
		if (msg.empty())
			return;

		string contents = "[" + getCurrentTimeLogFormatted() + "] " + formatCallFunction(extractCallerName(caller.function_name())) + " : " + msg + "\n";

		writeToLogFile(contents);
		agingLogFile();
	}

	~Logger() { };
private:
	string getCurrentTimeLogFormatted()
	{
		auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

		std::stringstream ss;
		ss << std::put_time(std::localtime(&now), "%y.%m.%d %H:%M");

		std::string formattedTime = ss.str();

		return ss.str();
	}

	string getCurrentTimeFileFormatted()
	{
		auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

		std::stringstream ss;
		ss << std::put_time(std::localtime(&now), "%y%m%d_%Hh_%Mm_%Ss");

		std::string formattedTime = ss.str();

		return ss.str();
	}

	string extractCallerName(const char* funcSig)
	{
		std::string sig(funcSig);
		size_t start = sig.find(" ") + 1;
		start = sig.find(" ", start) + 1;
		size_t end = sig.find("::", start);
		return sig.substr(start, end - start) + "()";
	}

	string formatCallFunction(string callFunction)
	{
		string formatCallFunction(30, ' ');
		size_t length = callFunction.size();
		if (length > 30)
			callFunction.resize(30);
		formatCallFunction.replace(0, length, callFunction);
		return formatCallFunction;
	}

	long long getFileSize(const std::string& filename)
	{
		std::ifstream file(filename, std::ios::binary | std::ios::ate);
		if (!file.is_open())
		{
			std::cerr << "Error: Unable to open file." << std::endl;
			return -1;
		}
		return file.tellg();
	}

	string getSaveFileName()
	{
		string result = "until_" + getCurrentTimeFileFormatted() + ".log";

		return result;
	}

	bool changeFileName(string from, string to)
	{
		std::wstring oldWstr(from.begin(), from.end());
		std::wstring newWstr(to.begin(), to.end());
		
		return MoveFile(oldWstr.c_str(), newWstr.c_str());
	}

	void writeToLogFile(string contents)
	{
		ofstream* latest;
		latest = new ofstream(LOGFILE, ios::app);
		latest->write(contents.c_str(), contents.size());
		latest->close();
		delete latest;
	}

	void agingLogFile()
	{
		if (fs::exists(LOGFILE))
		{
			if (getFileSize(LOGFILE) > TEN_KB)
			{
				string oldFileName = LOGFILE;
				string newFileName = getSaveFileName();
				if (changeFileName(oldFileName, newFileName))
				{
					logFileQueue.push(newFileName);
					if (logFileQueue.size() == 2)
					{
						doZip();
					}
				}
			}
		}
	}

	void doZip()
	{
		string oldFileName = logFileQueue.front();
		string newFileName = oldFileName;
		size_t dotIndex = newFileName.find_last_of('.');
		if (dotIndex != string::npos)
		{
			newFileName.replace(dotIndex, newFileName.size() - dotIndex, ".zip");
		}
		if (changeFileName(oldFileName, newFileName))
		{
			logFileQueue.pop();
		}
	}

	const string LOGFILE = "latest.log";
	const long long TEN_KB = 10240;
	queue<string> logFileQueue;
};