#include "Help.h"

bool Help::isValidArgs(const vector<string>& args)
{
	return VALID;
}

Progress Help::doCommand(const vector<string>& args)
{
	logger.print("Command : " + sliceString(args, 0));
	m_outputStream << m_helpMessage;
	return Progress::Continue;
}
