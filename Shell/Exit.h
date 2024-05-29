#pragma once

#include "CommandHandler.h"

using namespace std;

class Exit : public CommandHandler
{
public:
    Exit(ostream& _out, SsdHelper& _ssd) : CommandHandler(_out, _ssd) {};

    bool isValidArgs(const vector<string>& args) override;
    Progress doCommand(const vector<string>& args) override;
    string usage() override;;

    ~Exit() {};
};
