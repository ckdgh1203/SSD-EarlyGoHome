#include "ScriptTestFixture.cpp"
#include "../Shell/TestApp1.cpp"

class TestApp1Fixture : public ScriptTestFixture
{
protected:
    TestApp1 testScript{ redirectedOutput,ssd };
};

TEST_F(TestApp1Fixture, TestApp1FailureCase)
{
    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(200);
    EXPECT_CALL(ssdResultMock, get())
        .WillOnce(Return(testData))
        .WillOnce(Return(testData))
        .WillOnce(Return(testData))
        .WillRepeatedly(Return(dataZero));

    doScriptAndExpect(testScript, false);
}

TEST_F(TestApp1Fixture, TestApp1SuccessCase)
{
    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(200);
    EXPECT_CALL(ssdResultMock, get()).WillRepeatedly(Return(testData));

    doScriptAndExpect(testScript, true);
}