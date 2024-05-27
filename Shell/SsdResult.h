#pragma once

#include <string>
class ISsdResult
{
public:
    virtual std::string get(void) = 0;
};

class SsdResult : public ISsdResult
{
    std::string get(void) override
    {
        return std::string();
    }
};
