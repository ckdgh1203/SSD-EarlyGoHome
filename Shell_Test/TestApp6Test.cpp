#include "ScriptTestFixture.h"
#include "../Shell/TestApp6.cpp"

class TestApp6Fixture : public ScriptTestFixture
{
protected:
    TestApp6 testScript{ redirectedOutput,ssd };
};

TEST_F(TestApp6Fixture, TestApp6FailureCase)
{
    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(12);
    EXPECT_CALL(ssdResultMock, get()).WillRepeatedly(Return(testData));

    doScriptAndExpect(testScript, false);
}

TEST_F(TestApp6Fixture, TestApp6SuccessCase)
{
    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(12);
    EXPECT_CALL(ssdResultMock, get())
        .WillOnce(Return(testData))
        .WillOnce(Return(testData))
        .WillOnce(Return(testData))
        .WillOnce(Return("0x11111111"))
        .WillOnce(Return("0x11111111"));

    doScriptAndExpect(testScript, true);
}