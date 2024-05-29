#pragma once

#include "ScriptHandler.h"

class TestApp6 : public ScriptHandler
{
public:
    TestApp6(ostringstream& stringStream, SsdHelper& ssdHelper)
        : ScriptHandler(stringStream, ssdHelper)
    {}

    bool doScript() override;
    string usage(void) override { return "testapp6 or Write5to10AndWrite8to10AndReadCompare\n"; };
};