#pragma once

#include "CommandHandler.cpp"

#include <iostream>

using namespace std;

class Read : public CommandHandler
{
public:
	Read(ostream& _out, SsdHelper& _ssd) : CommandHandler(_out, _ssd) {};

	// read 99
	bool isValidArgs(const vector<string>& args) override
	{
		if (args.size() != 2)
			return INVALID;

		if (stoi(args[1]) < 0 || stoi(args[1]) > 99)
			return INVALID;

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
};