#pragma once

#include "CommandHandler.cpp"

class FullRead : public CommandHandler
{
public:
	FullRead() {};

	// CommandHandler을(를) 통해 상속됨
	bool isValidArgs(string args) override
	{
		return true;
	}

	~FullRead() {};
private:
};