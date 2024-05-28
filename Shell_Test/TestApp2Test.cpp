#include "ScriptTestFixture.cpp"
#include "../Shell/TestApp2.cpp"

class TestApp2Fixture : public ScriptTestFixture
{
protected:
    TestApp2 testScript{ redirectedOutput,ssd };
};

TEST_F(TestApp2Fixture, TestApp2FailureCase)
{
    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(192);
    EXPECT_CALL(ssdResultMock, get()).WillRepeatedly(Return("0xAAAABBBB"));

    doScriptAndExpect(testScript, false);
}

TEST_F(TestApp2Fixture, TestApp2SuccessCase)
{
    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(192);
    EXPECT_CALL(ssdResultMock, get()).WillRepeatedly(Return("0x12345678"));

    doScriptAndExpect(testScript, true);
}