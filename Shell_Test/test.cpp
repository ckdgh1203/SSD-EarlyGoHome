#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <sstream>

#include "../Shell/Shell.cpp"
#include "SsdMock.h"

using namespace std;
using namespace testing;

class ShellTestFixture : public Test
{
protected:
    NiceMock<SsdExcutalbeMock> ssdExecutableMock{};
    NiceMock<SsdResultMock> ssdResultMock{};

    Shell shell{ &ssdExecutableMock, &ssdResultMock, redirectedOutput};

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

    void writeAndExpect(string input, string expected)
    {
        shell.write(VALID_LBA, input);

        EXPECT_THAT(fetchOutput(), expected);
    }

    void runAndExpect(string& input, string& expected)
    {
        shell.run(istringstream(input));
        EXPECT_EQ(expected, fetchOutput());
    }

private:
    ostringstream redirectedOutput{};
};

TEST_F(ShellTestFixture, OutOfLbaRead)
{
    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(0);
    shell.read(INVALID_LBA);
    EXPECT_EQ("Out of Lba", fetchOutput());
}

TEST_F(ShellTestFixture, ReadSuccess)
{
    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(100);
    EXPECT_CALL(ssdResultMock, get())
        .Times(100)
        .WillRepeatedly(Return(dataZero));

    for (int lba = 0; lba < 100; lba++)
    {
        shell.read(lba);
        EXPECT_EQ(dataZero + "\n", fetchOutput());
    }
}

TEST_F(ShellTestFixture, OutOfLbaWrite)
{
    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(0);
    shell.write(INVALID_LBA, dataZero);
}

TEST_F(ShellTestFixture, InvalidDataFormatWrite)
{
    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(0);

    writeAndExpect("0x0", "[WARNING] Invalid input data length !!!\n");
    writeAndExpect("abcd123456", "[WARNING] Prefix '0x' was not included in input data !!!\n");
    writeAndExpect("0xabcd1234", "[WARNING] Input data has invalid characters !!!\n");
}

TEST_F(ShellTestFixture, WriteSuccess)
{
    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(1);
    shell.write(VALID_LBA, dataZero);
}

TEST_F(ShellTestFixture, FullWrite_NotIncludedPrefixException)
{
    string expected = "[WARNING] Prefix '0x' was not included in input data !!!\n";

    shell.fullwrite("abcd1234");

    EXPECT_THAT(fetchOutput(), Eq(expected));
}

TEST_F(ShellTestFixture, FullWrite_NotAllowedInputDataException)
{
    string expected = "[WARNING] Input data has invalid characters !!!\n";

    shell.fullwrite("0xabcd1234");

    EXPECT_THAT(fetchOutput(), Eq(expected));
}

TEST_F(ShellTestFixture, FullWrite_100TimesSuccessfully)
{
    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(100);

    shell.fullwrite("0xABCD1234");
}

TEST_F(ShellTestFixture, FullRead_100TimesSuccessfully)
{
    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(100);

    shell.fullread();
}

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

TEST_F(ShellTestFixture, DISABLED_RunAndRead)
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
        "Testable Exit\n";
    runAndExpect(inputString, expected);
}

TEST_F(ShellTestFixture, DISABLED_RunAndWrite)
{
    constexpr int NUMBER_OF_OPERATION = 2;
    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(NUMBER_OF_OPERATION);
    EXPECT_CALL(ssdResultMock, get()).Times(0);
    string inputString = "write 3 0x12345678\n"
        "write 99 0x12345678\n"
        "exit\n";
    string expected = "shell> " "shell> " "shell> "
        "Testable Exit\n";
    runAndExpect(inputString, expected);
}

TEST_F(ShellTestFixture, DISABLED_RunAndFullRead)
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
    expected += "shell> " "Testable Exit\n";
    runAndExpect(inputString, expected);
}

TEST_F(ShellTestFixture, DISABLED_RunAndFullWrite)
{
    constexpr int NUMBER_OF_OPERATION = 100;
    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(NUMBER_OF_OPERATION);
    EXPECT_CALL(ssdResultMock, get()).Times(0);
    string inputString = "fullwrite 0xDEADBEEF\n"
        "exit\n";

    string expected = "shell> " "shell> " "Testable Exit\n";
    runAndExpect(inputString, expected);
}


TEST_F(ShellTestFixture, DISABLED_RunAndHelp)
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
        "shell> " "Testable Exit\n";

    runAndExpect(inputString, expected);
}

TEST_F(ShellTestFixture, TestApp1FailureCase)
{
    string expected = "[WARNING] testapp1 : written data is different with read data!!!\n";

    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(200);
    EXPECT_CALL(ssdResultMock, get())
        .WillOnce(Return(testData))
        .WillOnce(Return(testData))
        .WillOnce(Return(testData))
        .WillRepeatedly(Return(dataZero));

    shell.doTestApp1();

    EXPECT_THAT(fetchOutput(), Eq(expected));
}

TEST_F(ShellTestFixture, TestApp1SuccessCase)
{
    string expected = "testapp1 : Done test, written data is same with read data :)\n";

    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(200);
    EXPECT_CALL(ssdResultMock, get()).WillRepeatedly(Return(testData));

    shell.doTestApp1();

    EXPECT_THAT(fetchOutput(), Eq(expected));
}

TEST_F(ShellTestFixture, TestApp2FailureCase)
{
    string expected = "[WARNING] testapp2 : written data is different with read data!!!\n";

    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(192);
    EXPECT_CALL(ssdResultMock, get()).WillRepeatedly(Return("0xAAAABBBB"));

    shell.doTestApp2();

    EXPECT_THAT(fetchOutput(), Eq(expected));
}

TEST_F(ShellTestFixture, TestApp2SuccessCase)
{
    string expected = "testapp2 : Done test, written data is same with read data :)\n";

    EXPECT_CALL(ssdExecutableMock, execute(_)).Times(192);
    EXPECT_CALL(ssdResultMock, get()).WillRepeatedly(Return("0x12345678"));

    shell.doTestApp2();

    EXPECT_THAT(fetchOutput(), Eq(expected));
}