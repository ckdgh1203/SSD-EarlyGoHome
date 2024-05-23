#pragma once

#include "CommandHandler.cpp"

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

    // CommandHandler을(를) 통해 상속됨
    bool isValidArgs(string args) override
    {
        return true;
    }

    ~Exit() {};

    void doExit() override
    {
        exit(0);
    }
private:
};