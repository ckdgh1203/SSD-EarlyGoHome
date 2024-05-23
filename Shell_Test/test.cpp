#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <sstream>

#include "../Shell/Shell.cpp"
#include "../Shell/SsdExcutable.h"

using namespace std;
using namespace testing;

class SsdExcutalbeMock : public ISsdExecutable
{
public:
	MOCK_METHOD(bool, execute, (const string&), (override));
private:
};

class TestableExitActor : public iExit
{
public:
	TestableExitActor(ostream& _out) : m_outputStream(_out) {}
	void doExit() override
	{
		m_outputStream << "Testable Exit" << endl;
	}
private:
	ostream& m_outputStream;
};

class ShellTestFixture : public Test
{
protected:
	NiceMock<SsdExcutalbeMock> ssdExecutableMock{};
	Shell shell{ &ssdExecutableMock, redirectedOutput };
	TestableExitActor testableExitActor{ redirectedOutput };

	static constexpr int INVALID_LBA = 100;
	static constexpr int VALID_LBA = 99;
	const string dataZero = "0x00000000";

	void SetUp(void) override
	{
		shell.setExit(&testableExitActor);
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

private:
	ostringstream redirectedOutput{};
};

TEST_F(ShellTestFixture, HelpCallTest)
{
	shell.help();
	auto& helpMessage = fetchOutput();

	shell.helpMessasge();
	auto& expectedMessage = fetchOutput();
	
	EXPECT_EQ(expectedMessage, helpMessage);
}

TEST_F(ShellTestFixture, ExitCallTest)
{
	shell.exit();
	auto& exitMessage = fetchOutput();

	testableExitActor.doExit();
	auto& expectedMessage = fetchOutput();

	EXPECT_EQ(exitMessage, expectedMessage);
}

TEST_F(ShellTestFixture, OutOfLbaRead)
{
	EXPECT_CALL(ssdExecutableMock, execute(_)).Times(0);

	EXPECT_EQ("Out of Lba", shell.read(INVALID_LBA));
}

TEST_F(ShellTestFixture, ReadSuccess)
{
	EXPECT_CALL(ssdExecutableMock, execute(_)).Times(100);

	for (int lba = 0; lba < 100; lba++)
	{
		EXPECT_EQ("0x00000000", shell.read(lba));
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
	EXPECT_CALL(ssdExecutableMock, execute(_)).Times(0);
	istringstream userInput("exit\n");

	shell.run(userInput);

	// should check result
}

TEST_F(ShellTestFixture, RunAndRead)
{
	EXPECT_CALL(ssdExecutableMock, execute(_)).Times(1);
	istringstream userInput("read 3\nexit\n");

	shell.run(userInput);
	
	// should check result
}

TEST_F(ShellTestFixture, TestApp1FailureCase)
{
	string expected = "[WARNING] testapp1 : written data is different with read data!!!\n";
	
	EXPECT_CALL(ssdExecutableMock, execute(_)).Times(200);

	shell.doTestApp1();

	EXPECT_THAT(fetchOutput(), Eq(expected));
}

TEST_F(ShellTestFixture, DISABLED_TestApp1SuccessCase)
{
	string expected = "testapp1 : Done test, written data is same with read data :)\n";

	EXPECT_CALL(ssdExecutableMock, execute(_)).Times(200);

	shell.doTestApp1();

	EXPECT_THAT(fetchOutput(), Eq(expected));
}