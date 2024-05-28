#pragma once

#include <string>
#include <iostream>

#include "Write.cpp"
#include "CommandHandler.cpp"

using namespace std;

class FullWrite : public CommandHandler
{
public:
	FullWrite(ostream& _out, SsdHelper& _ssd, Write* _write) : CommandHandler(_out, _ssd), write(_write){};
	// fullwrite 0x12345678
	bool isValidArgs(const vector<string>& args) override
	{
		if (args.size() != 2)
			return INVALID;

		for (int lba = START_LBA; lba < END_LBA; lba++)
		{
			nArgs.push_back({ "write", to_string(lba), args[1]});
			if (!write->isValidArgs(nArgs[lba]))
				return INVALID;
		}

		return VALID;
	}

	Progress doCommand(const vector<string>& args) override
	{
		logger.print("Command : " + sliceString(args, 0));
		for (int lba = START_LBA; lba < END_LBA; lba++)
		{
			write->doCommand(nArgs[lba]);
		}
		return Progress::Continue;
	}

	void usage() override {}

	~FullWrite() {};
private:
	Write* write;
	vector<vector<string>> nArgs;
};