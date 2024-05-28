#pragma once

#include "CommandHandler.h"

#include <iostream>
#include <mutex>

using namespace std;

class Exit : public CommandHandler
{
public:
    Exit(ostream& _out, SsdHelper& _ssd) : CommandHandler(_out, _ssd) {};


    bool isValidArgs(const vector<string>& args) override;

    Progress doCommand(const vector<string>& args) override;

    void usage() override {};

    ~Exit() {};

private:
};

inline bool Exit::isValidArgs(const vector<string>& args)
{
    if (args.size() != 1)
        return INVALID;

    return VALID;
}

inline Progress Exit::doCommand(const vector<string>& args)
{
    m_outputStream << "Exit from Shell" << endl;
    logger.print("Command : " + sliceString(args, 0));
    return Progress::Done;
}
