#pragma once

#include "CommandHandler.h"
#include "LbaRangeVerifier.h"

#include <iostream>

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

inline bool Read::isValidArgs(const vector<string>& args)
{
	if (isInvalidNumberOfArguments(args)) return INVALID;
	if (m_lbaRangeVerifier.isLbaOutOfRange(stoi(args[1]))) return INVALID;
	return VALID;
}

inline Progress Read::doCommand(const vector<string>& args)
{
	logger.print("Command : " + sliceString(args, 0));
	string arguments = "R " + args[1];
	m_ssdHelper.execute(arguments);
	m_outputStream << m_ssdHelper.getResult() << endl;
	return Progress::Continue;
}

inline bool Read::isInvalidNumberOfArguments(const std::vector<std::string>& args)
{
	return (args.size() != 2);
}
