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

	void print(string msg, const std::source_location& loc = std::source_location::current())
	{
		if (msg.empty())
			return;

		string buf(30, ' ');
		string callFunction = extractClassName(loc.function_name());
		callFunction += "()";
		formattingCallFunction(buf, callFunction);
		string result = "[" + getCurrentTimeLogFormatted() + "] " + buf + " : " + msg + "\n";

		if (fs::exists(LOGFILE))
		{
			long long fileSize = getFileSize(LOGFILE);
			if (fileSize > TEN_KB)
			{
				string oldFileName = LOGFILE;
				string newFileName = getSaveFileName();
				std::wstring oldWstr(oldFileName.begin(), oldFileName.end());
				std::wstring newWstr(newFileName.begin(), newFileName.end());
				MoveFile(oldWstr.c_str(), newWstr.c_str());
				logFileQueue.push(newFileName);
				if (logFileQueue.size() == 2)
				{
					zip();
				}
			}
			cout << "FileSize : " << fileSize << endl;
		}
		ofstream* latest;
		latest = new ofstream(LOGFILE, ios::app);
		latest->write(result.c_str(), result.size());
		latest->close();

		delete latest;
	}

	string getSaveFileName()
	{
		string result = "until_" + getCurrentTimeFileFormatted() + ".log";
		
		return result;
	}

	void zip()
	{
		string oldFileName = logFileQueue.front(); logFileQueue.pop();
		string newFileName = oldFileName;
		size_t dotIndex = newFileName.find_last_of('.');
		if (dotIndex != string::npos)
		{
			newFileName.replace(dotIndex, newFileName.size() - dotIndex, ".zip");
		}
		std::wstring oldWstr(oldFileName.begin(), oldFileName.end());
		std::wstring newWstr(newFileName.begin(), newFileName.end());
		MoveFile(oldWstr.c_str(), newWstr.c_str());

		cout << "Zip From" << oldFileName << " to " << newFileName << endl;
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

	string extractClassName(const char* funcSig)
	{
		std::string sig(funcSig);
		size_t start = sig.find(" ") + 1;
		start = sig.find(" ", start) + 1;
		size_t end = sig.find("::", start);
		return sig.substr(start, end - start);
	}

	string formattingCallFunction(string& buf, string callFunction)
	{
		size_t length = callFunction.size();
		if (length > 30)
			callFunction.resize(30);
		buf.replace(0, length, callFunction);
		return buf;
	}

	long long getFileSize(const std::string& filename)
	{
		std::ifstream file(filename, std::ios::binary | std::ios::ate);
		if (!file.is_open())
		{
			std::cerr << "Error: Unable to open file." << std::endl;
			return -1; // 파일 열기 실패
		}
		return file.tellg(); // 현재 위치가 파일의 끝인 파일 포인터의 위치를 반환하여 파일 크기를 구함
	}

	const string LOGFILE = "latest.log";
	const long long TEN_KB = 10240;
	queue<string> logFileQueue;
};