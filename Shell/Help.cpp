#include "Help.h"

Progress Help::doCommand(const vector<string>& args)
{
	logger.print("Command : " "help");
	m_outputStream << "Help:" << endl;
	for (auto& command : m_factory->getHandlerList())
	{
		m_outputStream << "\t" << command->usage();
	}
	m_outputStream << "\thelp\n";
	return Progress::Continue;
}
