#include "FullWrite.h"

bool FullWrite::isValidArgs(const vector<string>& args)
{
	if (args.size() != 2)
		return INVALID;

	for (int lba = START_LBA; lba < END_LBA; lba++)
	{
		nArgs.push_back({ "write", to_string(lba), args[1] });
		if (!write->isValidArgs(nArgs[lba]))
			return INVALID;
	}

	return VALID;
}

Progress FullWrite::doCommand(const vector<string>& args)
{
	logger.print("Command : " + sliceString(args, 0));
	for (int lba = START_LBA; lba < END_LBA; lba++)
	{
		write->doCommand(nArgs[lba]);
	}
	return Progress::Continue;
}
