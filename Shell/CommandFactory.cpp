#pragma once

#include "CommandHandler.cpp"
#include "Read.cpp"
#include "Write.cpp"
#include "FullRead.cpp"
#include "FullWrite.cpp"
#include "Help.cpp"
#include "Exit.cpp"

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
	CommandHandler* create(const string& commandStr)
	{
		CommandEnum commandEnum = stringToCommandEnum(commandStr);

		switch (commandEnum)
		{
		case CommandEnum::READ:
			return new Read();
		case CommandEnum::WRITE:
			return new Write();
		case CommandEnum::FULLREAD:
			return new FullRead();
		case CommandEnum::FULLWRITE:
			return new FullWrite();
		case CommandEnum::HELP:
			return new Help();
		case CommandEnum::EXIT:
			return new Exit();
		default:
			return nullptr;
		}
	}
private:
	CommandEnum stringToCommandEnum(const string& commandStr)
	{
		if (commandStr == "READ")
			return CommandEnum::READ;
		if (commandStr == "WRITE")
			return CommandEnum::WRITE;
		if (commandStr == "FULLREAD")
			return CommandEnum::FULLREAD;
		if (commandStr == "FULLWRITE")
			return CommandEnum::FULLWRITE;
		if (commandStr == "HELP")
			return CommandEnum::HELP;
		if (commandStr == "EXIT")
			return CommandEnum::EXIT;
		return CommandEnum::NUMOFCOMMAND;
	}
};