#pragma once

#include "CommandHandler.h"

#include <string>
#include <vector>

enum class CommandEnum
{
	READ = 0,
	WRITE,
	FULLREAD,
	FULLWRITE,
	ERASE,
	ERASE_RANGE,
	HELP,
	EXIT,
	NUMOFCOMMAND
};

class CommandFactory
{
public:
	CommandFactory(std::ostream& _out, SsdHelper& _ssd);

	CommandHandler* create(const std::string& commandStr);
private:
	CommandEnum stringToCommandEnum(const std::string& commandStr);
	std::vector<CommandHandler*> m_handlers{};
};
