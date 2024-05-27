#pragma once

#include <string>
#include <vector>

using namespace std;

enum class Progress
{
	Continue = 0,
	Done = 1,
};

class CommandHandler
{
public:
	CommandHandler(ostream& _out) : m_outputStream(_out){};

	virtual bool isValidArgs(const vector<string>& args) = 0;
	virtual Progress doCommand(const vector<string>& args) = 0;
	virtual void usage() = 0;

	virtual ~CommandHandler() {};
private:
protected:
	const static int startLBA = 0;
	const static int endLBA = 100;

	const static bool VALID = true;
	const static bool INVALID = false;

	ostream& m_outputStream;
};