#pragma once

#include "CommandHandler.cpp"

#include <iostream>

using namespace std;

class Write : public CommandHandler
{
public:
	Write() {};

	// write 123 0x12345678
	bool isValidArgs(const vector<string>& args) override
	{
		if (args.size() != 3)
			return INVALID;
		unsigned long test = stoul(args[1]);
		cout << test << endl;
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

	void doCommand(const vector<string>& args) override
	{
		logger.print("Command : " + sliceString(args, 0));
		cout << "Do Write!!!" << endl;
	}

	void usage() override {};

	~Write() {};
private:
};