#pragma once

#include "ScriptHandler.h"

class TestApp5 : public ScriptHandler
{
public:
    TestApp5(ostringstream& stringStream, SsdHelper& ssdHelper)
        : ScriptHandler(stringStream, ssdHelper)
    {}

    bool doScript() override;
    string usage(void) override { return "testapp5 or Write0Repeat10AndReadCompare\n"; };
};