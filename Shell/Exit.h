#pragma once
#include <cstdlib>

class iExit
{
public:
    virtual void doExit() = 0;
private:
};

class Exit : public iExit
{
public:
    void doExit() override
    {
        exit(0);
    }
private:
};
