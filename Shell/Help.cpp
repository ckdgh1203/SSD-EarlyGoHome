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
		cout << m_helpMessage;
	}

	void usage() override {};

	~Help() {};
private:
	const string m_helpMessage = "Help:\n"
		"\tread [LBA]\n"
		"\twrite [LBA] [DATA]\n"
		"\tfullread\n"
		"\tfullwrite [DATA]\n";
};