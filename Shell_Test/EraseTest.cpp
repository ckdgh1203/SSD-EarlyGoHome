#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Shell/Erase.cpp"
#include "SsdMock.h"
#include "OutputCapture.h"

using namespace testing;

class EraseTest : public Test, public OutputCapture
{
public:
    NiceMock<SsdExcutalbeMock> ssdExecutableMock{};
    NiceMock<SsdResultMock> ssdResultMock{};
    SsdHelper ssd{ &ssdExecutableMock, &ssdResultMock };
    Erase erase{ m_redirectedOutput, ssd };
};

TEST_F(EraseTest, DoCommand)
{
    EXPECT_CALL(ssdExecutableMock, execute("E 0 100")).Times(1);
    vector<string> args{ "erase", "0", "100"};
    EXPECT_TRUE(erase.isValidArgs(args));
    EXPECT_EQ(Progress::Continue, erase.doCommand(args));
}

TEST_F(EraseTest, InvalidStartLba)
{
    vector<string> args{ "erase", "100", "0"};
    EXPECT_FALSE(erase.isValidArgs(args));
}

TEST_F(EraseTest, InvalidEndLba)
{
    vector<string> args{ "erase", "10", "100" };
    EXPECT_FALSE(erase.isValidArgs(args));
}

TEST_F(EraseTest, InvalidNumberOfArgument)
{
    vector<string> args{ "erase", "100"};
    EXPECT_FALSE(erase.isValidArgs(args));
}