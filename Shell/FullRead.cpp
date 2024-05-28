#pragma once

#include "FullRead.h"

bool FullRead::isValidArgs(const vector<string>& args)
{
	if (args.size() != 1)
		return INVALID;

	for (int lba = START_LBA; lba < END_LBA; lba++)
	{
		nArgs.push_back({ "read", to_string(lba) });
		if (!read->isValidArgs(nArgs[lba]))
			return INVALID;
	}

	return VALID;
}

Progress FullRead::doCommand(const vector<string>& args)
{
	logger.print("Command : " + sliceString(args, 0));
	for (int lba = START_LBA; lba < END_LBA; lba++)
	{
		read->doCommand(nArgs[lba]);
	}
	return Progress::Continue;
}

void FullRead::usage()
{
	cout << "fullread" << endl;
}
