#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <sstream>

#include "../Shell/Shell.cpp"
#include "../Shell/Logger.cpp"
#include "SsdMock.h"

using namespace std;
using namespace testing;

class ShellTestFixture : public Test
{
protected:
    NiceMock<SsdExcutalbeMock> ssdExecutableMock{};
    NiceMock<SsdResultMock> ssdResultMock{};
    SsdHelper ssd{ &ssdExecutableMock, &ssdResultMock };
    Shell shell{ssd, redirectedOutput};

    static constexpr int INVALID_LBA = 100;
    static constexpr int VALID_LBA = 99;
    const string dataZero = "0x00000000";
    const string testData = "0xDEADC0DE";

    void SetUp(void) override
    {
    }

    string fetchOutput(void)
    {
        auto fetchedString = redirectedOutput.str();
        redirectedOutput.str("");
        redirectedOutput.clear();
        return fetchedString;
    }

    void runAndExpect(const string& input, string& expected)
    {
        auto ss = istringstream(input);
        shell.run(ss);
        EXPECT_EQ(expected, fetchOutput());
    }

private:
    ostringstream redirectedOutput{};
};

TEST_F(ShellTestFixture, RunAndExit)
{
    constexpr int NUMBER_OF_OPERATION = 0;
    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(NUMBER_OF_OPERATION);
    EXPECT_CALL(ssdResultMock, get()).Times(NUMBER_OF_OPERATION);
    string inputString = "exit\n";
    string expected = "shell> "
        "Exit from Shell\n";
    runAndExpect(inputString, expected);
}

TEST_F(ShellTestFixture, RunAndRead)
{
    constexpr int NUMBER_OF_OPERATION = 2;
    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(NUMBER_OF_OPERATION);
    EXPECT_CALL(ssdResultMock, get())
        .Times(NUMBER_OF_OPERATION)
        .WillRepeatedly(Return(dataZero));
    string inputString = "read 3\n"
        "read 99\n"
        "exit\n";
    string expected = "shell> "
        "0x00000000"
        "\nshell> "
        "0x00000000"
        "\nshell> "
        "Exit from Shell\n";
    runAndExpect(inputString, expected);
}

TEST_F(ShellTestFixture, RunAndWrite)
{
    constexpr int NUMBER_OF_OPERATION = 2;
    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(NUMBER_OF_OPERATION);
    EXPECT_CALL(ssdResultMock, get()).Times(0);
    string inputString = "write 3 0x12345678\n"
        "write 99 0x12345678\n"
        "exit\n";
    string expected = "shell> " "shell> " "shell> "
        "Exit from Shell\n";
    runAndExpect(inputString, expected);
}

TEST_F(ShellTestFixture, RunAndFullRead)
{
    constexpr int NUMBER_OF_OPERATION = 100;
    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(NUMBER_OF_OPERATION);
    EXPECT_CALL(ssdResultMock, get())
        .Times(NUMBER_OF_OPERATION)
        .WillRepeatedly(Return(dataZero));
    string inputString = "fullread\n"
        "exit\n";

    string expected = "shell> ";
    for (int i = 0; i < NUMBER_OF_OPERATION; i++)
    {
        expected += "0x00000000\n";
    }
    expected += "shell> " "Exit from Shell\n";
    runAndExpect(inputString, expected);
}

TEST_F(ShellTestFixture, RunAndFullWrite)
{
    constexpr int NUMBER_OF_OPERATION = 100;
    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(NUMBER_OF_OPERATION);
    EXPECT_CALL(ssdResultMock, get()).Times(0);
    string inputString = "fullwrite 0xDEADBEEF\n"
        "exit\n";

    string expected = "shell> " "shell> " "Exit from Shell\n";
    runAndExpect(inputString, expected);
}


TEST_F(ShellTestFixture, RunAndHelp)
{
    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(0);
    EXPECT_CALL(ssdResultMock, get()).Times(0);
    string inputString = "help\n"
        "exit\n";

    string expected = "shell> "
        "Help:\n"
        "\tread [LBA]\n"
        "\twrite [LBA] [DATA]\n"
        "\tfullread\n"
        "\tfullwrite [DATA]\n"
        "shell> " "Exit from Shell\n";

    runAndExpect(inputString, expected);
}