#pragma once

#include "CommandHandler.cpp"

#include <iostream>
#include "Read.cpp"

using namespace std;

class FullRead : public CommandHandler
{
public:
	FullRead(Read* _read) : read(_read) {};

	// fullread
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

	void commandBody(const vector<string>& args) override
	{
		for (int lba = startLBA; lba < endLBA; lba++)
		{
			read->doCommand(nArgs[lba]);
		}
	}

	string defaultLogMsg() override
	{
		return "FullRead!!";
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