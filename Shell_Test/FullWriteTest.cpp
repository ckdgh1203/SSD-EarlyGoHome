#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Shell/FullWrite.cpp"
#include "SsdMock.h"
#include "OutputCapture.h"

using namespace testing;

class FullWriteTest : public Test, public OutputCapture
{
public:
    NiceMock<SsdExcutalbeMock> ssdExecutableMock{};
    NiceMock<SsdResultMock> ssdResultMock{};
    FullWrite fullWrite{ redirectedOutput, ssd, &write };

private:
    SsdHelper ssd{ &ssdExecutableMock, &ssdResultMock };
    Write write{ redirectedOutput, ssd };
};

TEST_F(FullWriteTest, DoCommand)
{
    vector<string> args;
    args.push_back("fullwrite");
    args.push_back("0xABCD1234");

    EXPECT_TRUE(fullWrite.isValidArgs(args));
    EXPECT_EQ(Progress::Continue, fullWrite.doCommand(args));
}

TEST_F(FullWriteTest, FullWrite_NotIncludedPrefixException)
{
    string expected = "[WARNING] Prefix '0x' was not included in input data !!!\n";

    vector<string> args;
    args.push_back("fullwrite");
    args.push_back("abcd123456");

    EXPECT_FALSE(fullWrite.isValidArgs(args));

    EXPECT_THAT(fetchOutput(), Eq(expected));
}

TEST_F(FullWriteTest, FullWrite_NotAllowedInputDataException)
{
    string expected = "[WARNING] Input data has invalid characters !!!\n";

    vector<string> args;
    args.push_back("fullwrite");
    args.push_back("0xabcd1234");

    EXPECT_FALSE(fullWrite.isValidArgs(args));
    EXPECT_THAT(fetchOutput(), Eq(expected));
}

