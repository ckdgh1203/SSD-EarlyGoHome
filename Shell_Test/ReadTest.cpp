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
    Read read{ m_redirectedOutput, ssd };

    const string dataZero = "0x00000000";
};

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
    EXPECT_CALL(ssdResultMock, get())
        .Times(100)
        .WillRepeatedly(Return(dataZero));

    for (int lba = 0; lba < 100; lba++)
    {
        string lbaString = to_string(lba);
        EXPECT_CALL(ssdExecutableMock, execute("R " + lbaString )).Times(1);
        vector<string> args{ "read", lbaString };
        read.doCommand(args);
        EXPECT_EQ(dataZero + "\n", fetchOutput());
    }
}

TEST_F(ReadTest, InvalidNumberOfArgument)
{
    vector<string> args{ "read" };
    EXPECT_FALSE(read.isValidArgs(args));
}
