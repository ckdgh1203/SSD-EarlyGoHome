#include "Flush.h"

bool Flush::isValidArgs(const vector<string>& args)
{
	if (args.size() != 1)
		return INVALID;

	return VALID;
}

Progress Flush::doCommand(const vector<string>& args)
{
	logger.print("Command : " + sliceString(args, 0));
	string arguments = "F" ;
	m_ssdHelper.execute(arguments);

	return Progress::Continue;
}

string Flush::usage()
{
	return "flush\n";
}