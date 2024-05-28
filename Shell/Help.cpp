#include "Help.h"

bool Help::isValidArgs(const vector<string>& args)
{
	return VALID;
}

Progress Help::doCommand(const vector<string>& args)
{
	logger.print("Command : " + sliceString(args, 0));
	m_outputStream << "Help:" << endl;
	for (auto& command : m_factory->getHandlerList())
	{
		m_outputStream << "\t" << command->usage();
	}

	return Progress::Continue;
}

string Help::usage()
{
	return "help\n";
}
