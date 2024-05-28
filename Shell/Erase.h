#pragma once

#include "CommandHandler.h"
#include "LbaRangeVerifier.h"

using namespace std;

class Erase : public CommandHandler
{
public:
	Erase(ostream& _out, SsdHelper& _ssd) : CommandHandler(_out, _ssd) {};

	bool isValidArgs(const vector<string>& args) override;
	Progress doCommand(const vector<string>& args) override;
	string usage() override;;

	~Erase() {};
private:
	LbaRangeVerifier m_lbaRangeVerifier;
};
