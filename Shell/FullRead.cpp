#pragma once

#include "CommandHandler.h"

#include <iostream>
#include "Read.cpp"

using namespace std;

class FullRead : public CommandHandler
{
public:
	FullRead(ostream& _out, SsdHelper& _ssd, Read* _read) : CommandHandler(_out, _ssd), read(_read){};
	bool isValidArgs(const vector<string>& args) override;

	Progress doCommand(const vector<string>& args) override;

	void usage() override;

	~FullRead() {};
private:
	Read* read;
	vector<vector<string>> nArgs;
};

inline bool FullRead::isValidArgs(const vector<string>& args)
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

inline Progress FullRead::doCommand(const vector<string>& args)
{
	logger.print("Command : " + sliceString(args, 0));
	for (int lba = START_LBA; lba < END_LBA; lba++)
	{
		read->doCommand(nArgs[lba]);
	}
	return Progress::Continue;
}

inline void FullRead::usage()
{
	cout << "fullread" << endl;
}
