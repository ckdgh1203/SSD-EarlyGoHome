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

inline bool EraseRange::isValidArgs(const vector<string>& args)
{
	if (args.size() != 3)
		return INVALID;
	auto startLba = stoi(args[1]);
	if (m_lbaRangeVerifier.isLbaOutOfRange(startLba)) return INVALID;
	auto endLba = stoi(args[2]);
	if (m_lbaRangeVerifier.isLbaOutOfRange(endLba)) return INVALID;
	if (startLba > endLba) return INVALID;
	return VALID;
}

inline Progress EraseRange::doCommand(const vector<string>& args)
{
	logger.print("Command : " + sliceString(args, 0));
	auto numberOfLba = stoi(args[2]) - stoi(args[1]) + 1;
	string arguments = "E " + args[1] + " " + to_string(numberOfLba);
	m_ssdHelper.execute(arguments);
	m_outputStream << m_ssdHelper.getResult() << endl;
	return Progress::Continue;
}
