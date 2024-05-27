#pragma once

#include "CommandHandler.cpp"
#include "DataFormatVerifier.h"
#include <iostream>

using namespace std;

class Write : public CommandHandler
{
public:
	Write(ostream& _out, SsdHelper& _ssd) :
		CommandHandler(_out, _ssd), m_dataFormatVerifier(_out){};

	bool isValidArgs(const vector<string>& args) override
	{
		if (isInvalidNumberOfArguments(args)) return INVALID;
		if (isLbaOutOfRange(args[1])) return INVALID;
		if (m_dataFormatVerifier.isInvalidDataFormat(args[2])) return INVALID;

		return VALID;
	}

	Progress doCommand(const vector<string>& args) override
	{
		logger.print("Command : " + sliceString(args, 0));
		string arguments = "W " + args[1] + " " + args[2];
		m_ssdHelper.execute(arguments);
		return Progress::Continue;
	}

	void usage() override {};

	~Write() {};

	bool isInvalidNumberOfArguments(const std::vector<std::string>& args)
	{
		return (args.size() != 3);
	}

	bool isLbaOutOfRange(const string& lbaString)
	{
		return stoi(lbaString) < 0 || stoi(lbaString) > 99;
	}
private:
	DataFormatVerifier m_dataFormatVerifier;
};