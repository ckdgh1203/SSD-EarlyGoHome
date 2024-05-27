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
	virtual void doCommand(const vector<string>& args) = 0;
	virtual void usage() = 0;

	virtual ~CommandHandler() {};
private:
protected:
	const static int startLBA = 0;
	const static int endLBA = 100;

	const static bool VALID = true;
	const static bool INVALID = false;

	//Logger logger;
};