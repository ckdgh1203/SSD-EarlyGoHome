#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Shell/Write.cpp"
#include "SsdMock.h"

using namespace testing;

class WriteTest : public Test
{
public:
    NiceMock<SsdExcutalbeMock> ssdExecutableMock{};
    NiceMock<SsdResultMock> ssdResultMock{};
    SsdHelper ssd{ &ssdExecutableMock, &ssdResultMock };
    Write write{ redirectedOutput, ssd };

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

TEST_F(WriteTest, DoCommand)
{
    vector<string> args;
    args.push_back("write");
    args.push_back("0");
    args.push_back("0x00000000");

    EXPECT_EQ(Progress::Continue, write.doCommand(args));
}

TEST_F(WriteTest, OutOfRangeWrite)
{
    static const string INVALID_LBA = "100";
    vector<string> args;
    args.push_back("write");
    args.push_back(INVALID_LBA);
    args.push_back("0x00000000");
    EXPECT_FALSE(write.isValidArgs(args));
}

TEST_F(WriteTest, WriteSuccess)
{
    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(100);

    for (int lba = 0; lba < 100; lba++)
    {
        vector<string> args;
        args.push_back("write");
        args.push_back(to_string(lba));
        args.push_back("0x00000000");

        write.doCommand(args);
    }
}