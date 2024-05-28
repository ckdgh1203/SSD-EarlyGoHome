#include "ScriptTestFixture.cpp"
#include "../Shell/TestApp5.cpp"

class TestApp5Fixture : public ScriptTestFixture
{
protected:
    TestApp5 testScript{ redirectedOutput,ssd };
};

TEST_F(TestApp5Fixture, TestApp5FailureCase)
{
    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(11);
    EXPECT_CALL(ssdResultMock, get()).WillOnce(Return(dataZero));

    doScriptAndExpect(testScript, false);
}

TEST_F(TestApp5Fixture, TestApp5SuccessCase)
{
    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(11);
    EXPECT_CALL(ssdResultMock, get()).WillOnce(Return(testData));

    doScriptAndExpect(testScript, true);
}