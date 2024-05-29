#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Shell/Write.cpp"
#include "SsdMock.h"
#include "OutputCapture.h"

using namespace testing;

class WriteTest : public Test, public OutputCapture
{
public:
    NiceMock<SsdExcutalbeMock> ssdExecutableMock{};
    NiceMock<SsdResultMock> ssdResultMock{};
    SsdHelper ssd{ &ssdExecutableMock, &ssdResultMock };
    Write write{ m_redirectedOutput, ssd };

    void VerifyDataAndExpect(string input, string expected)
    {
        vector<string> args{ "write", VALID_LBA, input };
        write.isValidArgs(args);

        EXPECT_THAT(fetchOutput(), expected);
    }

    const string dataZero = "0x00000000";
    const string VALID_LBA = "99";
};

TEST_F(WriteTest, OutOfRangeWrite)
{
    static const string INVALID_LBA = "100";
    vector<string> args{ "write", INVALID_LBA, dataZero };

    EXPECT_FALSE(write.isValidArgs(args));
}

TEST_F(WriteTest, WriteSuccess)
{
    for (int lba = 0; lba < 100; lba++)
    {
        string lbaString = to_string(lba);
        EXPECT_CALL(ssdExecutableMock, execute("W " + lbaString + " " + dataZero)).Times(1);
        vector<string> args{ "write", lbaString, dataZero };

        EXPECT_EQ(Progress::Continue, write.doCommand(args));
    }
}

TEST_F(WriteTest, InvalidDataFormatWrite)
{
    VerifyDataAndExpect("0x0", "[WARNING] Invalid input data length !!!\n");
    VerifyDataAndExpect("abcd123456", "[WARNING] Prefix '0x' was not included in input data !!!\n");
    VerifyDataAndExpect("0xabcd1234", "[WARNING] Input data has invalid characters !!!\n");
}

TEST_F(WriteTest, InvalidNumberOfArgument)
{
    vector<string> args{ "write", "0" };
    EXPECT_FALSE(write.isValidArgs(args));
}
