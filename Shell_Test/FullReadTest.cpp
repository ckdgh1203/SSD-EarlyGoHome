#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Shell/FullRead.cpp"
#include "SsdMock.h"

using namespace testing;

class FullReadTest : public Test
{
public:
    NiceMock<SsdExcutalbeMock> ssdExecutableMock{};
    NiceMock<SsdResultMock> ssdResultMock{};
    FullRead fullRead{ redirectedOutput, ssd, &read };

    string fetchOutput(void)
    {
        auto fetchedString = redirectedOutput.str();
        redirectedOutput.str("");
        redirectedOutput.clear();
        return fetchedString;
    }

    const string dataZero = "0x00000000";

private:
    SsdHelper ssd{ &ssdExecutableMock, &ssdResultMock };
    Read read{ redirectedOutput, ssd };
    ostringstream redirectedOutput{};
};


TEST_F(FullReadTest, DoCommand)
{
    vector<string> args;
    args.push_back("fullread");

    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(100);
    EXPECT_CALL(ssdResultMock, get())
        .Times(100)
        .WillRepeatedly(Return(dataZero));

    EXPECT_TRUE(fullRead.isValidArgs(args));
    EXPECT_EQ(Progress::Continue, fullRead.doCommand(args));
}
