#include "ScriptTestFixture.h"
#include "../Shell/TestApp4.cpp"

class TestApp4Fixture : public ScriptTestFixture
{
protected:
    TestApp4 testScript{ redirectedOutput,ssd };
};

TEST_F(TestApp4Fixture, TestApp4FailureCase)
{
    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(100);
    EXPECT_CALL(ssdResultMock, get())
        .WillOnce(Return(dataZero))
        .WillOnce(Return(dataZero))
        .WillRepeatedly(Return(testData));

    doScriptAndExpect(testScript, false);
}

TEST_F(TestApp4Fixture, TestApp4SuccessCase)
{
    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(100);
    EXPECT_CALL(ssdResultMock, get()).WillRepeatedly(Return(testData));

    doScriptAndExpect(testScript, true);
}