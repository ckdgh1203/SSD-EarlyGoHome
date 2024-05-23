#pragma once

#include "CommandHandler.cpp"

class Write : public CommandHandler
{
public:
	Write() {};

	// CommandHandler을(를) 통해 상속됨
	bool isValidArgs(string args) override
	{
		return true;
	}

	~Write() {};
private:
};