#pragma once

#include "CommandHandler.h"
#include "DataFormatVerifier.h"
#include "LbaRangeVerifier.h"
#include <iostream>

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

inline bool Write::isValidArgs(const vector<string>& args)
{
	if (isInvalidNumberOfArguments(args)) return INVALID;
	if (m_lbaRangeVerifier.isLbaOutOfRange(stoi(args[1]))) return INVALID;
	if (m_dataFormatVerifier.isInvalidDataFormat(args[2])) return INVALID;

	return VALID;
}

inline Progress Write::doCommand(const vector<string>& args)
{
	logger.print("Command : " + sliceString(args, 0));
	string arguments = "W " + args[1] + " " + args[2];
	m_ssdHelper.execute(arguments);
	return Progress::Continue;
}

inline bool Write::isInvalidNumberOfArguments(const std::vector<std::string>& args)
{
	return (args.size() != 3);
}
