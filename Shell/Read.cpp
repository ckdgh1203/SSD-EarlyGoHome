#include "Read.h"

bool Read::isValidArgs(const vector<string>& args)
{
	if (isInvalidNumberOfArguments(args)) return INVALID;
	if (m_lbaRangeVerifier.isInvalidLba(args[1])) return INVALID;
	return VALID;
}

Progress Read::doCommand(const vector<string>& args)
{
	logger.print("Command : " + sliceString(args, 0));
	string arguments = "R " + args[1];
	m_ssdHelper.execute(arguments);
	m_outputStream << m_ssdHelper.getResult() << endl;
	return Progress::Continue;
}

string Read::usage() 
{
	return "read [LBA]\n";
}

bool Read::isInvalidNumberOfArguments(const std::vector<std::string>& args)
{
	return (args.size() != 2);
}
