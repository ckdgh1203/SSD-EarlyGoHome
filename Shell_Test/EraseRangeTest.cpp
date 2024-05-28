#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Shell/EraseRange.cpp"
#include "SsdMock.h"

using namespace testing;

class EraseRangeTest : public Test
{
public:
    NiceMock<SsdExcutalbeMock> ssdExecutableMock{};
    NiceMock<SsdResultMock> ssdResultMock{};
    SsdHelper ssd{ &ssdExecutableMock, &ssdResultMock };
    EraseRange eraseRange{ redirectedOutput, ssd };

    string fetchOutput(void)
    {
        auto fetchedString = redirectedOutput.str();
        redirectedOutput.str("");
        redirectedOutput.clear();
        return fetchedString;
    }

    const string dataZero = "0x00000000";

private:
    ostringstream redirectedOutput{};
};

TEST_F(EraseRangeTest, DoCommand)
{
    EXPECT_CALL(ssdExecutableMock, execute("E 0 100")).Times(1);
    vector<string> args{ "erase_range", "0", "99" };
    EXPECT_TRUE(eraseRange.isValidArgs(args));
    EXPECT_EQ(Progress::Continue, eraseRange.doCommand(args));
}

TEST_F(EraseRangeTest, InvalidStartLba)
{
    vector<string> args{ "erase_range", "100", "0" };
    EXPECT_FALSE(eraseRange.isValidArgs(args));
}

TEST_F(EraseRangeTest, InvalidEndLba)
{
    vector<string> args{ "erase_range", "10", "100" };
    EXPECT_FALSE(eraseRange.isValidArgs(args));
}

TEST_F(EraseRangeTest, InvalidRange)
{
    vector<string> args{ "erase_range", "99", "0" };
    EXPECT_FALSE(eraseRange.isValidArgs(args));

}
TEST_F(EraseRangeTest, InvalidNumberOfArgument)
{
    vector<string> args{ "erase_range", "100" };
    EXPECT_FALSE(eraseRange.isValidArgs(args));
}