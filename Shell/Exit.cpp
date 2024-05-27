#pragma once

#include "CommandHandler.cpp"

#include <iostream>
#include <mutex>

using namespace std;

class iExit : public CommandHandler
{
public:
    virtual void doExit() = 0;
    virtual bool isTest() = 0;
private:
};

class Exit : public iExit
{
public:
    Exit() {};

    bool isValidArgs(const vector<string>& args) override
    {
        if (args.size() != 1)
            return INVALID;

        return VALID;
    }

    void doCommand(const vector<string>& args) override
    {
        logger.print("Command : " + sliceString(args, 0));
        exit(0);
    }

    void doExit() override
    {
        exit(0);
    }

    void usage() override {};

    ~Exit() {};

    bool isTest() override
    {
        return false;
    }
private:
};