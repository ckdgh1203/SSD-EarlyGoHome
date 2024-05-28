#pragma once

#include "CommandHandler.h"
#include "DataFormatVerifier.h"
#include "LbaRangeVerifier.h"

using namespace std;

class Write : public CommandHandler
{
public:
	Write(ostream& _out, SsdHelper& _ssd) :
		CommandHandler(_out, _ssd), m_dataFormatVerifier(_out){};

	bool isValidArgs(const vector<string>& args) override;

	Progress doCommand(const vector<string>& args) override;

	void usage() override {};

	~Write() {};

	bool isInvalidNumberOfArguments(const std::vector<std::string>& args);

private:
	DataFormatVerifier m_dataFormatVerifier;
	LbaRangeVerifier m_lbaRangeVerifier;
};
