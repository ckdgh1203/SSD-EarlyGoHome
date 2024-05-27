#pragma once

#include <string>
#include <iostream>

#include "Write.cpp"
#include "CommandHandler.cpp"

using namespace std;

class FullWrite : public CommandHandler
{
public:
	FullWrite(Write* _write) : write(_write) {};

	// fullwrite 0x12345678
	bool isValidArgs(const vector<string>& args) override
	{
		if (args.size() != 2)
			return INVALID;

		for (int lba = startLBA; lba < endLBA; lba++)
		{
			nArgs.push_back({ "write", to_string(lba), args[1]});
			if (!write->isValidArgs(nArgs[lba]))
				return INVALID;
		}

		return VALID;
	}

	void doCommand(const vector<string>& args) override
	{
		logger.print("Command : " + sliceString(args, 0));
		for (int lba = startLBA; lba < endLBA; lba++)
		{
			write->doCommand(nArgs[lba]);
		}
	}

	void usage() override {}

	~FullWrite() {};
private:
	Write* write;
	vector<vector<string>> nArgs;
};