#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../Shell/TestApp1.cpp"
#include "../Shell/TestApp2.cpp"
#include "SsdMock.h"

using namespace testing;

class ScriptTestFixture : public Test
{
protected:
	NiceMock<SsdExcutalbeMock> ssdExecutableMock{};
	NiceMock<SsdResultMock> ssdResultMock{};
    ostringstream redirectedOutput{};
    CommandFactory commandFactory{ redirectedOutput, ssd };

    const string dataZero = "0x00000000";
    const string testData = "0xDEADC0DE";

    string fetchOutput(void)
    {
        auto fetchedString = redirectedOutput.str();
        redirectedOutput.str("");
        redirectedOutput.clear();
        return fetchedString;
    }

    void doScriptAndExpect(ScriptHandler& scriptHandler, string expected)
    {
        scriptHandler.doScript();
        EXPECT_THAT(fetchOutput(), expected);
    }

private:
    SsdHelper ssd{ &ssdExecutableMock, &ssdResultMock };
};

class TestApp1Fixture : public ScriptTestFixture
{
protected:
    TestApp1 testScript{ commandFactory, redirectedOutput };
};

class TestApp2Fixture : public ScriptTestFixture
{
protected:
    TestApp2 testScript{ commandFactory, redirectedOutput };
};

TEST_F(TestApp1Fixture, TestApp1FailureCase)
{
    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(200);
    EXPECT_CALL(ssdResultMock, get())
        .WillOnce(Return(testData))
        .WillOnce(Return(testData))
        .WillOnce(Return(testData))
        .WillRepeatedly(Return(dataZero));

    string expected = "[WARNING] testapp1 : written data is different with read data!!!\n";

    doScriptAndExpect(testScript, expected);
}

TEST_F(TestApp1Fixture, TestApp1SuccessCase)
{
    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(200);
    EXPECT_CALL(ssdResultMock, get()).WillRepeatedly(Return(testData));

    string expected = "testapp1 : Done test, written data is same with read data :)\n";

    doScriptAndExpect(testScript, expected);
}

TEST_F(TestApp2Fixture, TestApp2FailureCase)
{
    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(192);
    EXPECT_CALL(ssdResultMock, get()).WillRepeatedly(Return("0xAAAABBBB"));

    string expected = "[WARNING] testapp2 : written data is different with read data!!!\n";

    doScriptAndExpect(testScript, expected);
}

TEST_F(TestApp2Fixture, TestApp2SuccessCase)
{
    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(192);
    EXPECT_CALL(ssdResultMock, get()).WillRepeatedly(Return("0x12345678"));

    string expected = "testapp2 : Done test, written data is same with read data :)\n";

    doScriptAndExpect(testScript, expected);
}