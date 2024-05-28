#pragma once

#include "ScriptHandler.h"

class TestApp2 : public ScriptHandler
{
public:
    TestApp2(ostringstream& stringStream, SsdHelper& ssdHelper)
        : ScriptHandler(stringStream, ssdHelper) {}

    bool doScript() override;
};