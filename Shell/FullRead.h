#pragma once

#include <iostream>
#include "Read.h"

using namespace std;

class FullRead : public CommandHandler
{
public:
	FullRead(ostream& _out, SsdHelper& _ssd, Read* _read) : CommandHandler(_out, _ssd), read(_read){};
	bool isValidArgs(const vector<string>& args) override;

	Progress doCommand(const vector<string>& args) override;

	void usage() override;

	~FullRead() {};
private:
	Read* read;
	vector<vector<string>> nArgs;
};
