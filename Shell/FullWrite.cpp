#pragma once

#include <string>
#include <iostream>

#include "Write.cpp"
#include "CommandHandler.h"

using namespace std;

class FullWrite : public CommandHandler
{
public:
	FullWrite(ostream& _out, SsdHelper& _ssd, Write* _write) : CommandHandler(_out, _ssd), write(_write){};

	bool isValidArgs(const vector<string>& args) override;

	Progress doCommand(const vector<string>& args) override;

	void usage() override {}

	~FullWrite() {};
private:
	Write* write;
	vector<vector<string>> nArgs;
};

inline bool FullWrite::isValidArgs(const vector<string>& args)
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

inline Progress FullWrite::doCommand(const vector<string>& args)
{
	logger.print("Command : " + sliceString(args, 0));
	for (int lba = START_LBA; lba < END_LBA; lba++)
	{
		write->doCommand(nArgs[lba]);
	}
	return Progress::Continue;
}
