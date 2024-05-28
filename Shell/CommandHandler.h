#pragma once

#include "SsdHelper.h"
#include "Logger.h"
#include <string>
#include <iostream>
#include <vector>

enum class Progress
{
	Continue = 0,
	Done = 1,
};

using namespace std;

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

	std::string sliceString(const std::vector<std::string>& words, size_t start)
	{
		string result;
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

	std::ostream& m_outputStream;
	SsdHelper& m_ssdHelper;
	Logger logger;
};
