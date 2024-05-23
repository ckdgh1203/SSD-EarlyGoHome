#pragma once

#include "CommandHandler.cpp"

#include <iostream>

using namespace std;

class Help : public CommandHandler
{
public:
	Help() {};

	bool isValidArgs(const vector<string>& args) override
	{
		return VALID;
	}

	void doCommand(const vector<string>& args) override
	{
		cout << "Do Help!!!" << endl;
	}

	void usage() override {};

	~Help() {};
private:
};