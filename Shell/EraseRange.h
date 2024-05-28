#pragma once

#include "CommandHandler.h"
#include "LbaRangeVerifier.h"

#include <iostream>

using namespace std;

class EraseRange : public CommandHandler
{
public:
	EraseRange(ostream& _out, SsdHelper& _ssd) : CommandHandler(_out, _ssd) {};

	bool isValidArgs(const vector<string>& args) override;
	Progress doCommand(const vector<string>& args) override;
	void usage() override {};

	~EraseRange() {};
private:
	LbaRangeVerifier m_lbaRangeVerifier;
};
