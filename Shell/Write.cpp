#pragma once

#include "CommandHandler.cpp"

#include <iostream>

using namespace std;

class Write : public CommandHandler
{
public:
	Write(ostream& _out, SsdHelper& _ssd) : CommandHandler(_out, _ssd) {};

	// write 123 0x12345678
	bool isValidArgs(const vector<string>& args) override
	{
		if (args.size() != 3)
			return INVALID;
		unsigned long test = stoul(args[1]);

		if (stoi(args[1]) < 0 || stoi(args[1]) > 99)
			return INVALID;

		if (args[2].size() != 10)
			return INVALID;

		if (args[2][0] != '0' || args[2][1] != 'x')
			return INVALID;

		for (int i = 2; i < 10; i++)
		{
			if (!isxdigit(args[2][i]))
				return INVALID;
		}

		return VALID;
	}

	Progress doCommand(const vector<string>& args) override
	{
		string arguments = "W " + args[1] + " " + args[2] + "\n";
		m_ssdHelper.execute(arguments);
		return Progress::Continue;
	}

	void usage() override {};

	~Write() {};
private:
};