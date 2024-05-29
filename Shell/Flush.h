#pragma once

#include "CommandHandler.h"

using namespace std;

class Flush : public CommandHandler
{
public:
	Flush(ostream& _out, SsdHelper& _ssd) : CommandHandler(_out, _ssd) {};

	bool isValidArgs(const vector<string>& args) override;

	Progress doCommand(const vector<string>& args) override;

	string usage() override;;

	~Flush() {};
};