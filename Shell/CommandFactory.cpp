#pragma once

#include "CommandHandler.cpp"
#include "Read.cpp"
#include "Write.cpp"
#include "FullRead.cpp"
#include "FullWrite.cpp"
#include "Help.cpp"
#include "Exit.cpp"
#include <iostream>
#include <string>

using namespace std;

enum class CommandEnum
{
	READ = 0,
	WRITE,
	FULLREAD,
	FULLWRITE,
	HELP,
	EXIT,
	NUMOFCOMMAND
};

class CommandFactory
{
public:
	CommandHandler* create(const string& commandStr, iExit *_exit)
	{
		CommandEnum commandEnum = stringToCommandEnum(commandStr);

		switch (commandEnum)
		{
		case CommandEnum::READ:
			return new Read();
		case CommandEnum::WRITE:
			return new Write();
		case CommandEnum::FULLREAD:
			return new FullRead(new Read());
		case CommandEnum::FULLWRITE:
			return new FullWrite(new Write());
		case CommandEnum::HELP:
			return new Help();
		case CommandEnum::EXIT:
			return _exit;
		default:
			return nullptr;
		}
	}
private:
	CommandEnum stringToCommandEnum(const string& commandStr)
	{
		if (commandStr == "read")
			return CommandEnum::READ;
		if (commandStr == "write")
			return CommandEnum::WRITE;
		if (commandStr == "fullread")
			return CommandEnum::FULLREAD;
		if (commandStr == "fullwrite")
			return CommandEnum::FULLWRITE;
		if (commandStr == "help")
			return CommandEnum::HELP;
		if (commandStr == "exit")
			return CommandEnum::EXIT;
		return CommandEnum::NUMOFCOMMAND;
	}
};