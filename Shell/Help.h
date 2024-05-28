#pragma once

#include "CommandHandler.h"
#include "CommandFactory.h"

using namespace std;

class Help
{
public:
	Help(ostream& _out, CommandFactory* factory) :
		m_outputStream(_out),
		m_factory(factory) {}

	Progress doCommand(const vector<string>& args);

	~Help() {};
protected:
	ostream& m_outputStream;
	CommandFactory* m_factory;
	Logger& logger = Logger::getInstance();
};
