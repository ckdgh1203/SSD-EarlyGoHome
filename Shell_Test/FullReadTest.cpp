#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Shell/FullRead.cpp"
#include "SsdMock.h"
#include "OutputCapture.h"

using namespace testing;

class FullReadTest : public Test, public OutputCapture
{
public:
    NiceMock<SsdExcutalbeMock> ssdExecutableMock{};
    NiceMock<SsdResultMock> ssdResultMock{};
    FullRead fullRead{ m_redirectedOutput, ssd, &read };

    const string dataZero = "0x00000000";

private:
    SsdHelper ssd{ &ssdExecutableMock, &ssdResultMock };
    Read read{ m_redirectedOutput, ssd };
};


TEST_F(FullReadTest, DoCommand)
{
    vector<string> args{"fullread"};

    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(100);
    EXPECT_CALL(ssdResultMock, get())
        .Times(100)
        .WillRepeatedly(Return(dataZero));

    EXPECT_TRUE(fullRead.isValidArgs(args));
    EXPECT_EQ(Progress::Continue, fullRead.doCommand(args));
}

TEST_F(FullReadTest, InvalidNumberOfArgument)
{
    vector<string> args{};
    EXPECT_FALSE(fullRead.isValidArgs(args));
}
