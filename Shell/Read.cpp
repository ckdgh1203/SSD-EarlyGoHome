#pragma once

#include "CommandHandler.cpp"

#include <iostream>

using namespace std;

class Read : public CommandHandler
{
public:
	Read() {};

	// read 99
	bool isValidArgs(const vector<string>& args) override
	{
		if (args.size() != 2)
			return INVALID;

		if (stoi(args[1]) < 0 || stoi(args[1]) > 99)
			return INVALID;

		return VALID;
	}

	void commandBody(const vector<string>& args) override
	{
		cout << "Do Read!!!" << endl;
	}

	string defaultLogMsg() override
	{
		return "Read";
	}

	void usage() override {};

	~Read() {};
private:
};