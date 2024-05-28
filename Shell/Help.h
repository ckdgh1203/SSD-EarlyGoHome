#pragma once

#include "CommandHandler.h"
#include "CommandFactory.h"

using namespace std;

class Help : public CommandHandler
{
public:
	Help(ostream& _out, SsdHelper& _ssd, CommandFactory* factory) :
		CommandHandler(_out, _ssd), m_factory(factory) {};

	bool isValidArgs(const vector<string>& args) override;

	Progress doCommand(const vector<string>& args) override;

	string usage() override;;

	~Help() {};
protected:

	CommandFactory* m_factory;
};
