#pragma once

#include "CommandHandler.cpp"

#include <iostream>

using namespace std;

class iExit
{
public:
    virtual void doExit() = 0;
private:
};

class Exit : public iExit, public CommandHandler
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
        exit(0);
    }

    void usage() override {};

    ~Exit() {};

    void doExit() override
    {
        exit(0);
    }
private:
};