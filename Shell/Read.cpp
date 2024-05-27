#pragma once

#include "CommandHandler.cpp"

#include <iostream>

using namespace std;

class Read : public CommandHandler
{
public:
	Read(ostream& _out, SsdHelper& _ssd) : CommandHandler(_out, _ssd) {};

	bool isValidArgs(const vector<string>& args) override
	{
		if (isInvalidNumberOfArguments(args)) return INVALID;
		if (isLbaOutOfRange(args[1])) return INVALID;
		return VALID;
	}

	Progress doCommand(const vector<string>& args) override
	{
		logger.print("Command : " + sliceString(args, 0));
		string arguments = "R " + args[1];
		m_ssdHelper.execute(arguments);
		m_outputStream << m_ssdHelper.getResult() << endl;
		return Progress::Continue;
	}

	void usage() override {};

	~Read() {};
private:

	bool isLbaOutOfRange(const string& lbaString)
	{
		return stoi(lbaString) < 0 || stoi(lbaString) > 99;
	}

	bool isInvalidNumberOfArguments(const std::vector<std::string>& args)
	{
		return (args.size() != 2);
	}
};