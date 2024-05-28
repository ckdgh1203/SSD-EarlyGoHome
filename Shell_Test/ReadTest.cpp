#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Shell/Read.cpp"
#include "SsdMock.h"
#include "OutputCapture.h"

using namespace testing;

class ReadTest : public Test, public OutputCapture
{
public:
    NiceMock<SsdExcutalbeMock> ssdExecutableMock{};
    NiceMock<SsdResultMock> ssdResultMock{};
    SsdHelper ssd{ &ssdExecutableMock, &ssdResultMock };
    Read read{ redirectedOutput, ssd };

    const string dataZero = "0x00000000";
};

TEST_F(ReadTest, DoCommand)
{
    vector<string> args;
    args.push_back("read");
    args.push_back("0");
    EXPECT_EQ(Progress::Continue, read.doCommand(args));
}

TEST_F(ReadTest, OutOfLbaRead)
{
    static const string INVALID_LBA = "100";
    vector<string> args;
    args.push_back("read");
    args.push_back(INVALID_LBA);
    EXPECT_FALSE(read.isValidArgs(args));
}

TEST_F(ReadTest, ReadSuccess)
{
    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(100);
    EXPECT_CALL(ssdResultMock, get())
        .Times(100)
        .WillRepeatedly(Return(dataZero));

    for (int lba = 0; lba < 100; lba++)
    {
        vector<string> args;
        args.push_back("read");
        args.push_back(to_string(lba));
        read.doCommand(args);
        EXPECT_EQ(dataZero + "\n", fetchOutput());
    }
}