#pragma once
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

#include <string>
#include <source_location>
#include <queue>

#include "ZipAlgo.h"
#include "SimpleZip.h"

class Logger
{
public:
	static Logger& getInstance()
	{
		static Logger instance{};
		return instance;
	}
	Logger() 
	{
		// TODO - Stategy Pattern but not Factory.
		setZipAlgo(std::make_unique<SimpleZip>());
	};
	Logger& operator=(const Logger& other) = delete;
	Logger(const Logger& other) = delete;

	void print(std::string msg, const std::source_location& caller = std::source_location::current());
	void clean();

	void setZipAlgo(std::unique_ptr<ZipAlgo> algorithm);

	~Logger() { };

private:
	std::string getCurrentTimeLogFormatted();
	std::string getCurrentTimeFileFormatted();
	std::string extractCallerName(const char* funcSig);
	std::string formatCallFunction(std::string callFunction);
	long long getFileSize(const std::string& filename);
	std::string getSaveFileName();
	bool changeFileName(std::string from, std::string to);
	void writeToLogFile(std::string contents);
	void agingLogFile();
	void doZip();

	const std::string LOGFILE = "latest.log";
	const long long TEN_KB = 10240;
	std::queue<std::string> logFileQueue;

	std::unique_ptr<ZipAlgo> zipAlgorithm;
};