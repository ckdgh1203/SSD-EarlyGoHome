#pragma once

#include "CommandHandler.cpp"

#include <iostream>
#include "Read.cpp"

using namespace std;

class FullRead : public CommandHandler
{
public:
	FullRead(ostream& _out, SsdHelper& _ssd, Read* _read) : CommandHandler(_out, _ssd), read(_read){};
	bool isValidArgs(const vector<string>& args) override
	{
		if (args.size() != 1)
			return INVALID;

		for (int lba = startLBA; lba < endLBA; lba++)
		{
			nArgs.push_back({ "read", to_string(lba)});
			if (!read->isValidArgs(nArgs[lba]))
				return INVALID;
		}

		return VALID;
	}

	Progress doCommand(const vector<string>& args) override
	{
		for (int lba = startLBA; lba < endLBA; lba++)
		{
			read->doCommand(nArgs[lba]);
		}
		return Progress::Continue;
	}

	void usage() override 
	{
		cout << "fullread" << endl;
	}

	~FullRead() {};
private:
	Read* read;
	vector<vector<string>> nArgs;
};