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
	CommandFactory(void)
	{
		m_handlers.clear();
		m_handlers.reserve(static_cast<size_t>(CommandEnum::NUMOFCOMMAND));
		auto* readObject = new Read();
		m_handlers.push_back(readObject);
		auto* writeObject = new Write();
		m_handlers.push_back(writeObject);
		m_handlers.push_back(new FullRead(readObject));
		m_handlers.push_back(new FullWrite(writeObject));
		m_handlers.push_back(new Help());
		m_handlers.push_back(new Exit());
	}
	~CommandFactory(void)
	{
		for (auto& handler : m_handlers)
		{
			if(handler != nullptr) delete handler;
		}
	}
	CommandHandler* create(const string& commandStr)
	{
		CommandEnum commandEnum = stringToCommandEnum(commandStr);
		if (commandEnum == CommandEnum::NUMOFCOMMAND) return nullptr;
		return m_handlers[static_cast<size_t>(commandEnum)];
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
	vector<CommandHandler*> m_handlers{};
};