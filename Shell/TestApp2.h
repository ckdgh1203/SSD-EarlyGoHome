#pragma once

#include "ScriptHandler.h"

class TestApp2 : public ScriptHandler
{
public:
    TestApp2(ostringstream& stringStream, SsdHelper& ssdHelper)
        : ScriptHandler(stringStream, ssdHelper) {}

    bool doScript() override;
    string usage(void) override { return "testapp2 or Write0to6Repeat30AndWrite0to6AndReadCompare\n"; };
};