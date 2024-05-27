#pragma once

#include "CommandHandler.cpp"

#include <iostream>
#include <mutex>

using namespace std;

class Exit : public CommandHandler
{
public:
    Exit(ostream& _out, SsdHelper& _ssd) : CommandHandler(_out, _ssd) {};


    bool isValidArgs(const vector<string>& args) override
    {
        if (args.size() != 1)
            return INVALID;

        return VALID;
    }

    Progress doCommand(const vector<string>& args) override
    {
        m_outputStream << "Exit from Shell" << endl;
        logger.print("Command : " + sliceString(args, 0));
        return Progress::Done;
    }

    void usage() override {};

    ~Exit() {};

private:
};