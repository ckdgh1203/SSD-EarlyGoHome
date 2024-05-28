#pragma once

#include "ScriptHandler.h"

class TestApp6 : public ScriptHandler
{
public:
    TestApp6(ostringstream& stringStream, SsdHelper& ssdHelper)
        : ScriptHandler(stringStream, ssdHelper)
    {}

    bool doScript() override;
};