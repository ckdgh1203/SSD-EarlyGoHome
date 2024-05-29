#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <sstream>

#include "../Shell/Shell.cpp"
#include "../Shell/Logger.cpp"
#include "SsdMock.h"
#include "OutputCapture.h"

using namespace std;
using namespace testing;

class ShellTestFixture : public Test, public OutputCapture
{
protected:
    NiceMock<SsdExcutalbeMock> ssdExecutableMock{};
    NiceMock<SsdResultMock> ssdResultMock{};
    SsdHelper ssd{ &ssdExecutableMock, &ssdResultMock };
    Shell shell{ssd, m_redirectedOutput};

    const string dataZero = "0x00000000";

    void runAndExpect(const string& input, const string& expected)
    {
        auto ss = istringstream(input);
        shell.run(ss);
        EXPECT_EQ(expected, fetchOutput());
    }
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

    const string expectedMessage = "shell> "
        "Help:\n"
        "\tread [LBA]\n"
        "\twrite [LBA] [DATA]\n"
        "\tfullread\n"
        "\tfullwrite [DATA]\n"
        "\terase [START_LBA] [NUMBER_OF_LBA]\n"
        "\terase_range [START_LBA] [END_LBA]\n"
        "\texit\n"
        "\ttestapp1 or FullWriteAndFullReadAndCompare\n"
        "\ttestapp2 or Write0to6Repeat30AndWrite0to6AndReadCompare\n"
        "\ttestapp3 or FullWriteAndRead99AndCompare\n"
        "\ttestapp4 or FullReadAndCompare\n"
        "\ttestapp5 or Write0Repeat10AndReadCompare\n"
        "\ttestapp6 or Write5to10AndWrite8to10AndReadCompare\n"
        "\thelp\n"
        "shell> " "Exit from Shell\n";

    runAndExpect(inputString, expectedMessage);
}

TEST_F(ShellTestFixture, RunAndInvalidCommand)
{
    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(0);
    EXPECT_CALL(ssdResultMock, get()).Times(0);
    string inputString = "reda 3\n"
        "\n"
        "      \n"
        " help\n"
        "exit\n";

    const string expectedMessage = "shell> "
        "\nINVALID COMMAND\n"
        "shell> "
        "shell> "
        "\nINVALID COMMAND\n"
        "shell> "
        "\nINVALID COMMAND\n"
        "shell> " "Exit from Shell\n";

    runAndExpect(inputString, expectedMessage);
}

TEST_F(ShellTestFixture, RunAndInvalidArguments)
{
    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(0);
    EXPECT_CALL(ssdResultMock, get()).Times(0);
    string inputString = "read A\n"
        "write abcd1234\n"
        "erase 1 100\n"
        "erase_range 100 1\n"
        "exit\n";

    const string expectedMessage = "shell> "
        "\nINVALID COMMAND\n"
        "read [LBA]\n"
        "shell> "
        "\nINVALID COMMAND\n"
        "write [LBA] [DATA]\n"
        "shell> "
        "\nINVALID COMMAND\n"
        "erase [START_LBA] [NUMBER_OF_LBA]\n"
        "shell> "
        "\nINVALID COMMAND\n"
        "erase_range [START_LBA] [END_LBA]\n"
        "shell> " "Exit from Shell\n";

    runAndExpect(inputString, expectedMessage);
}

TEST_F(ShellTestFixture, RunAndTestApp1)
{
    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(200);
    EXPECT_CALL(ssdResultMock, get())
        .Times(100)
        .WillRepeatedly(Return("0xDEADC0DE"));
    string inputString = "testapp1 A\n"
        "exit\n";

    const string expectedMessage = "shell> "
        "testapp1 Pass!\n\n"
        "shell> " "Exit from Shell\n";

    runAndExpect(inputString, expectedMessage);
}

TEST_F(ShellTestFixture, RunAndTestApps)
{
    EXPECT_CALL(ssdResultMock, get()).WillRepeatedly(Return("0xDEADC0DE"));
    string inputString =
        "testapp3 A\n"
        "testapp4 A\n"
        "testapp5 A\n"
        "exit\n";

    const string expectedMessage = "shell> "
        "testapp3 Pass!\n\n"
        "shell> "
        "testapp4 Pass!\n\n"
        "shell> "
        "testapp5 Pass!\n\n"
        "shell> " "Exit from Shell\n";

    runAndExpect(inputString, expectedMessage);
}

TEST_F(ShellTestFixture, RunnerSucceed)
{
    EXPECT_CALL(ssdResultMock, get()).WillRepeatedly(Return("0xDEADC0DE"));

    shell.runRunner("run_list.lst");
}

TEST_F(ShellTestFixture, RunnerWithInvalidFileName)
{
    shell.runRunner("invalid.file");
}

TEST_F(ShellTestFixture, RunnerWithInvalidRunList)
{
    shell.runRunner("invalid_run_list.lst");
}