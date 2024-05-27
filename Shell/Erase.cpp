#pragma once

#include "CommandHandler.cpp"

#include <iostream>

using namespace std;
class Erase : public CommandHandler
{
public:
	Erase(ostream& _out, SsdHelper& _ssd) : CommandHandler(_out, _ssd) {};
	bool isValidArgs(const vector<string>& args) override
	{
		if (args.size() != 3)
			return INVALID;
		auto startLba = stoi(args[1]);
		if (startLba < 0 || startLba > 99)
			return INVALID;
		auto endLba = stoi(args[2]) + startLba - 1;
		if (endLba < 0 || endLba > 99)
			return INVALID;
		return VALID;
	}

	Progress doCommand(const vector<string>& args) override
	{
		logger.print("Command : " + sliceString(args, 0));
		string arguments = "E " + args[1] + " " + args[2];
		m_ssdHelper.execute(arguments);
		m_outputStream << m_ssdHelper.getResult() << endl;
		return Progress::Continue;
	}

	void usage() override {};

	~Erase() {};
private:
};