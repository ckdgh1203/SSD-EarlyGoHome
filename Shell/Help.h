#pragma once

#include "CommandHandler.h"
#include "CommandFactory.h"
#include "ScriptFactory.h"

using namespace std;

class Help
{
public:
	Help(ostream& _out, SsdHelper& _ssd, CommandFactory* commandFactory, ScriptFactory* scriptFactory) :
		m_outputStream(_out),
		m_ssdHelper(_ssd),
		m_commandFactory(commandFactory),
		m_scriptFactory(scriptFactory) {}

	Progress doCommand(const vector<string>& args);

	~Help() {};
protected:
	ostream& m_outputStream;
	CommandFactory* m_commandFactory;
	ScriptFactory* m_scriptFactory;
	SsdHelper& m_ssdHelper;
	Logger& logger = Logger::getInstance();
};
