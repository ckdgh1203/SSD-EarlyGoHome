#pragma once

#include <string>
#include <vector>
#include "Logger.cpp"

using namespace std;

class CommandHandler
{
public:
	CommandHandler() {};

	virtual bool isValidArgs(const vector<string>& args) = 0;
	virtual void usage() = 0;
	virtual void doCommand(const vector<string>& args) = 0;
	virtual ~CommandHandler() {};
private:
protected:
	const static int startLBA = 0;
	const static int endLBA = 100;

	const static bool VALID = true;
	const static bool INVALID = false;

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

	Logger logger;
};