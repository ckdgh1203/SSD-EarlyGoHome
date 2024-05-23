#pragma once

#include <string>

using namespace std;

class CommandHandler
{
public:
	CommandHandler() {};

	virtual bool isValidArgs(string args) = 0;

	~CommandHandler() {};
private:
};