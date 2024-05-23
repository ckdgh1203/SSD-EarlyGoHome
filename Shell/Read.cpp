#pragma once

#include "CommandHandler.cpp"

class Read : public CommandHandler
{
public:
	Read() {};

	// CommandHandler을(를) 통해 상속됨
	bool isValidArgs(string args) override
	{
		return true;
	}

	~Read() {};
private:
};