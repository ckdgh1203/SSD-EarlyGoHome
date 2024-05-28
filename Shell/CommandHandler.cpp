#pragma once

#include "SsdHelper.h"
#include <string>
#include <vector>
#include "Logger.cpp"

using namespace std;

enum class Progress
{
	Continue = 0,
	Done = 1,
};

class CommandHandler
{
public:
	CommandHandler(ostream& _out, SsdHelper& _ssd) :
		m_outputStream(_out), m_ssdHelper(_ssd) {};

	virtual bool isValidArgs(const vector<string>& args) = 0;
	virtual Progress doCommand(const vector<string>& args) = 0;
	virtual void usage() = 0;
	virtual ~CommandHandler() {};
private:
protected:
	constexpr static int START_LBA = 0;
	constexpr static int END_LBA = 100;

	constexpr static bool VALID = true;
	constexpr static bool INVALID = false;

	string sliceString(const std::vector<std::string>& words, size_t start)
	{
		std::string result;
		for (size_t i = start; i < words.size(); ++i)
		{
			result += words[i];
			if (i != words.size() - 1)
			{
				result += " ";
			}
		}
		return result;
	}

	ostream& m_outputStream;
	SsdHelper& m_ssdHelper;
	Logger logger;
};