#include "Help.h"

Progress Help::doCommand(const vector<string>& args)
{
	logger.print("Command : " "help");
	m_outputStream << "Help:" << endl;
	for (auto& command : m_commandFactory->getHandlerList())
	{
		m_outputStream << "\t" << command->usage();
	}
	for (auto& script : m_scriptFactory->getCommandList())
	{
		m_outputStream << "\t" << m_scriptFactory->create(script, m_ssdHelper)->usage();
	}
	m_outputStream << "\thelp\n";
	return Progress::Continue;
}
