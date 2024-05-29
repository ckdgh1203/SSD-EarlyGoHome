#pragma once

#include "ScriptHandler.h"

class TestApp3 : public ScriptHandler
{
public:
    TestApp3(ostringstream& stringStream, SsdHelper& ssdHelper)
        : ScriptHandler(stringStream, ssdHelper)
    {}

    bool doScript() override;
    string usage(void) override { return "testapp3 or FullWriteAndRead99AndCompare\n"; };
};