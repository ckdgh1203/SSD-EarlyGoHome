#pragma once

#include "CommandHandler.cpp"

#include <iostream>

using namespace std;

class Read : public CommandHandler
{
public:
	Read(ostream& _out) : CommandHandler(_out) {};

	// read 99
	bool isValidArgs(const vector<string>& args) override
	{
		if (args.size() != 2)
			return INVALID;

		if (stoi(args[1]) < 0 || stoi(args[1]) > 99)
			return INVALID;

		return VALID;
	}

	Progress doCommand(const vector<string>& args) override
	{
		cout << "Do Read!!!" << endl;
		return Progress::Continue;
	}

	void usage() override {};

	~Read() {};
private:
};