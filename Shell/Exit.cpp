#pragma once

#include "CommandHandler.cpp"

#include <iostream>
#include <mutex>

using namespace std;

class Exit : public CommandHandler
{
public:
    Exit() {};

    bool isValidArgs(const vector<string>& args) override
    {
        if (args.size() != 1)
            return INVALID;

        return VALID;
    }

    Progress doCommand(const vector<string>& args) override
    {
        return Progress::Done;
    }

    void usage() override {};

    ~Exit() {};

private:
};