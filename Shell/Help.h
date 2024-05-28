#pragma once

#include "CommandHandler.h"

#include <iostream>

using namespace std;

class Help : public CommandHandler
{
public:
	Help(ostream& _out, SsdHelper& _ssd) : CommandHandler(_out, _ssd) {};

	bool isValidArgs(const vector<string>& args) override;

	Progress doCommand(const vector<string>& args) override;

	void usage() override {};

	~Help() {};
protected:
	const string m_helpMessage = "Help:\n"
		"\tread [LBA]\n"
		"\twrite [LBA] [DATA]\n"
		"\tfullread\n"
		"\tfullwrite [DATA]\n";
};
