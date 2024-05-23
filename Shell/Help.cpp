#pragma once

#include "CommandHandler.cpp"

class Help : public CommandHandler
{
public:
	Help() {};

	// CommandHandler을(를) 통해 상속됨
	bool isValidArgs(string args) override
	{
		return true;
	}

	~Help() {};
private:
};