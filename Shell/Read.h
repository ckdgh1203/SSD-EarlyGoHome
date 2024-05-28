#pragma once

#include "CommandHandler.h"
#include "LbaRangeVerifier.h"

using namespace std;

class Read : public CommandHandler
{
public:
	Read(ostream& _out, SsdHelper& _ssd) : CommandHandler(_out, _ssd) {};

	bool isValidArgs(const vector<string>& args) override;

	Progress doCommand(const vector<string>& args) override;

	void usage() override {};

	~Read() {};
private:
	LbaRangeVerifier m_lbaRangeVerifier;

	bool isInvalidNumberOfArguments(const std::vector<std::string>& args);
};
