#pragma once

#include "ScriptHandler.h"

using namespace std;

class TestApp4 : public ScriptHandler
{
public:
    TestApp4(ostringstream& stringStream, SsdHelper& ssdHelper)
        : ScriptHandler(stringStream, ssdHelper)
    {}

    bool doScript() override;
    string usage(void) override { return "testapp4 or FullReadAndCompare\n"; };
};