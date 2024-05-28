#include "Logger.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <filesystem>

namespace fs = std::filesystem;

void Logger::print(std::string msg, const std::source_location& caller)
{
	if (msg.empty())
		return;

	std::string contents = "[" + getCurrentTimeLogFormatted() + "] " + formatCallFunction(extractCallerName(caller.function_name())) + " : " + msg + "\n";

	writeToLogFile(contents);
	agingLogFile();
}

std::string Logger::getCurrentTimeLogFormatted()
{
	auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	std::stringstream ss;
	ss << std::put_time(std::localtime(&now), "%y.%m.%d %H:%M");

	std::string formattedTime = ss.str();

	return ss.str();
}

std::string Logger::getCurrentTimeFileFormatted()
{
	auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	std::stringstream ss;
	ss << std::put_time(std::localtime(&now), "%y%m%d_%Hh_%Mm_%Ss");

	std::string formattedTime = ss.str();

	return ss.str();
}

std::string Logger::extractCallerName(const char* funcSig)
{
	std::string sig(funcSig);
	size_t start = sig.find(" ") + 1;
	start = sig.find(" ", start) + 1;
	size_t end = sig.find("::", start);
	return sig.substr(start, end - start) + "()";
}

std::string Logger::formatCallFunction(std::string callFunction)
{
	std::string formatCallFunction(30, ' ');
	size_t length = callFunction.size();
	if (length > 30)
		callFunction.resize(30);
	formatCallFunction.replace(0, length, callFunction);
	return formatCallFunction;
}

long long Logger::getFileSize(const std::string& filename)
{
	std::ifstream file(filename, std::ios::binary | std::ios::ate);
	if (!file.is_open())
	{
		std::cerr << "Error: Unable to open file." << std::endl;
		return -1;
	}
	return file.tellg();
}

std::string& Logger::getSaveFileName()
{
	std::string result = "until_" + getCurrentTimeFileFormatted() + ".log";

	return result;
}

bool Logger::changeFileName(std::string from, std::string to)
{
	std::wstring oldWstr(from.begin(), from.end());
	std::wstring newWstr(to.begin(), to.end());

	return MoveFile(oldWstr.c_str(), newWstr.c_str());
}

void Logger::writeToLogFile(std::string contents)
{
	std::ofstream* latest;
	latest = new std::ofstream(LOGFILE, std::ios::app);
	latest->write(contents.c_str(), contents.size());
	latest->close();
	delete latest;
}

void Logger::agingLogFile()
{
	if (fs::exists(LOGFILE))
	{
		if (getFileSize(LOGFILE) > TEN_KB)
		{
			std::string oldFileName = LOGFILE;
			std::string newFileName = getSaveFileName();
			if (changeFileName(oldFileName, newFileName))
			{
				logFileQueue.push(newFileName);

				std::cout << "Enqueue!!! : " << newFileName << " : " << logFileQueue.size() << std::endl;
				if (logFileQueue.size() == 2)
				{
					doZip();
				}
				std::cout << "Enqueue and...!!! : " << newFileName << " : " << logFileQueue.size() << std::endl;
			}
		}
	}
}

void Logger::doZip()
{
	if (logFileQueue.empty())
	{
		return;
	}
	std::string oldFileName = logFileQueue.front();
	std::string newFileName = oldFileName;
	size_t dotIndex = newFileName.find_last_of('.');
	std::cout << "Dozip : " << oldFileName << std::endl;
	if (dotIndex != std::string::npos)
	{
		newFileName.replace(dotIndex, newFileName.size() - dotIndex, ".zip");
	}
	if (changeFileName(oldFileName, newFileName))
	{
		logFileQueue.pop();
	}
}

void Logger::clean()
{
	std::cout << "Cleanup : " << logFileQueue.size() << std::endl;

	while (!logFileQueue.empty())
	{
		std::cout << "????" << std::endl;
		doZip();
	}
}