#pragma once

#include "CommandHandler.h"
#include "LbaRangeVerifier.h"

#include <iostream>

using namespace std;
class Erase : public CommandHandler
{
public:
	Erase(ostream& _out, SsdHelper& _ssd) : CommandHandler(_out, _ssd) {};
	bool isValidArgs(const vector<string>& args) override;

	Progress doCommand(const vector<string>& args) override;

	void usage() override {};

	~Erase() {};
private:
	LbaRangeVerifier m_lbaRangeVerifier;
};

inline bool Erase::isValidArgs(const vector<string>& args)
{
	if (args.size() != 3)
		return INVALID;
	auto startLba = stoi(args[1]);
	if (m_lbaRangeVerifier.isLbaOutOfRange(startLba)) return INVALID;
	auto endLba = stoi(args[2]) + startLba - 1;
	if (m_lbaRangeVerifier.isLbaOutOfRange(endLba)) return INVALID;

	return VALID;
}

inline Progress Erase::doCommand(const vector<string>& args)
{
	logger.print("Command : " + sliceString(args, 0));
	string arguments = "E " + args[1] + " " + args[2];
	m_ssdHelper.execute(arguments);
	m_outputStream << m_ssdHelper.getResult() << endl;
	return Progress::Continue;
}
