#include "CommandFactory.h"
#include "CommandHandler.h"
#include "Read.cpp"
#include "Write.cpp"
#include "FullRead.cpp"
#include "FullWrite.cpp"
#include "Erase.cpp"
#include "EraseRange.cpp"
#include "Help.cpp"
#include "Exit.cpp"
#include "SsdHelper.h"

using namespace std;

inline CommandFactory::CommandFactory(ostream& _out, SsdHelper& _ssd)
{
	m_handlers.clear();
	m_handlers.reserve(static_cast<size_t>(CommandEnum::NUMOFCOMMAND));
	auto* readObject = new Read(_out, _ssd);
	m_handlers.push_back(readObject);
	auto* writeObject = new Write(_out, _ssd);
	m_handlers.push_back(writeObject);
	m_handlers.push_back(new FullRead(_out, _ssd, readObject));
	m_handlers.push_back(new FullWrite(_out, _ssd, writeObject));
	m_handlers.push_back(new Erase(_out, _ssd));
	m_handlers.push_back(new EraseRange(_out, _ssd));
	m_handlers.push_back(new Help(_out, _ssd));
	m_handlers.push_back(new Exit(_out, _ssd));
}

inline CommandHandler* CommandFactory::create(const string& commandStr)
{
	CommandEnum commandEnum = stringToCommandEnum(commandStr);
	if (commandEnum == CommandEnum::NUMOFCOMMAND) return nullptr;
	return m_handlers[static_cast<size_t>(commandEnum)];
}

inline CommandEnum CommandFactory::stringToCommandEnum(const string& commandStr)
{
	if (commandStr == "read")
		return CommandEnum::READ;
	if (commandStr == "write")
		return CommandEnum::WRITE;
	if (commandStr == "fullread")
		return CommandEnum::FULLREAD;
	if (commandStr == "fullwrite")
		return CommandEnum::FULLWRITE;
	if (commandStr == "erase")
		return CommandEnum::ERASE;
	if (commandStr == "erase_range")
		return CommandEnum::ERASE_RANGE;
	if (commandStr == "help")
		return CommandEnum::HELP;
	if (commandStr == "exit")
		return CommandEnum::EXIT;
	return CommandEnum::NUMOFCOMMAND;
}
