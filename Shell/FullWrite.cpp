#pragma once

#include "CommandHandler.cpp"

class FullWrite : public CommandHandler
{
public:
	FullWrite() {};

	// CommandHandler을(를) 통해 상속됨
	bool isValidArgs(string args) override
	{
		return true;
	}

	~FullWrite() {};
private:
};