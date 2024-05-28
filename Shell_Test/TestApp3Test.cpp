#include "ScriptTestFixture.cpp"
#include "../Shell/TestApp3.cpp"

class TestApp3Fixture : public ScriptTestFixture
{
protected:
    TestApp3 testScript{ redirectedOutput,ssd };
};

TEST_F(TestApp3Fixture, TestApp3FailureCase)
{
    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(101);
    EXPECT_CALL(ssdResultMock, get()).WillOnce(Return(dataZero));

    doScriptAndExpect(testScript, false);
}

TEST_F(TestApp3Fixture, TestApp3SuccessCase)
{
    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(101);
    EXPECT_CALL(ssdResultMock, get()).WillOnce(Return(testData));

    doScriptAndExpect(testScript, true);
}