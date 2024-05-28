#include "Write.h"

bool Write::isValidArgs(const vector<string>& args)
{
	if (isInvalidNumberOfArguments(args)) return INVALID;
	if (m_lbaRangeVerifier.isLbaOutOfRange(stoi(args[1]))) return INVALID;
	if (m_dataFormatVerifier.isInvalidDataFormat(args[2])) return INVALID;

	return VALID;
}

Progress Write::doCommand(const vector<string>& args)
{
	logger.print("Command : " + sliceString(args, 0));
	string arguments = "W " + args[1] + " " + args[2];
	m_ssdHelper.execute(arguments);
	return Progress::Continue;
}

bool Write::isInvalidNumberOfArguments(const std::vector<std::string>& args)
{
	return (args.size() != 3);
}
