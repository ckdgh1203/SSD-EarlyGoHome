#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../Shell/ScriptHandler.h"
#include "SsdMock.h"

using namespace testing;

class ScriptTestFixture : public Test
{
protected:
    NiceMock<SsdExcutalbeMock> ssdExecutableMock{};
    NiceMock<SsdResultMock> ssdResultMock{};
    ostringstream redirectedOutput{};
    SsdHelper ssd{ &ssdExecutableMock, &ssdResultMock };

    const string dataZero = "0x00000000";
    const string testData = "0xDEADC0DE";

    inline void doScriptAndExpect(ScriptHandler& scriptHandler, bool expected)
    {
        EXPECT_THAT(scriptHandler.doScript(), Eq(expected));
    }
};