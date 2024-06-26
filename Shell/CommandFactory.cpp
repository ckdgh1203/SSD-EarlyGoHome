#include "CommandFactory.h"
#include "CommandHandler.h"
#include "Read.h"
#include "Write.h"
#include "FullRead.h"
#include "FullWrite.h"
#include "Erase.h"
#include "EraseRange.h"
#include "Exit.h"
#include "Flush.h"
#include "SsdHelper.h"

using namespace std;

CommandFactory::CommandFactory(ostream& _out, SsdHelper& _ssd)
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
	m_handlers.push_back(new Exit(_out, _ssd));
	m_handlers.push_back(new Flush(_out, _ssd));
}

CommandHandler* CommandFactory::create(const string& commandStr)
{
	CommandEnum commandEnum = stringToCommandEnum(commandStr);
	if (commandEnum == CommandEnum::NUMOFCOMMAND) return nullptr;
	return m_handlers[static_cast<size_t>(commandEnum)];
}

const std::vector<CommandHandler*>& CommandFactory::getHandlerList(void)
{
	return m_handlers;
}

CommandEnum CommandFactory::stringToCommandEnum(const string& commandStr)
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
	if (commandStr == "exit")
		return CommandEnum::EXIT;
	if (commandStr == "flush")
		return CommandEnum::FLUSH;
	return CommandEnum::NUMOFCOMMAND;
}
