#pragma once

#include <string>

#include "Write.h"
#include "CommandHandler.h"

using namespace std;

class FullWrite : public CommandHandler
{
public:
	FullWrite(ostream& _out, SsdHelper& _ssd, Write* _write) : CommandHandler(_out, _ssd), write(_write){};

	bool isValidArgs(const vector<string>& args) override;

	Progress doCommand(const vector<string>& args) override;

	string usage() override;

	~FullWrite() {};
private:
	Write* write;
	vector<vector<string>> nArgs;
};
