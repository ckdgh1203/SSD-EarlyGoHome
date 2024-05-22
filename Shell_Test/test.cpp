#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <sstream>

#include "../Shell/Shell.cpp"
#include "../SSD/iSSD.h"
#include "../Shell/SsdExcutable.h"

using namespace std;
using namespace testing;

class SsdMock : public iSSD
{
public:
	MOCK_METHOD(void, write, (int, string), (override));
	MOCK_METHOD(void, read, (int), (override));
private:
};

class SsdExcutalbeMock : public ISsdExecutable
{
public:
	MOCK_METHOD(bool, execute, (const string&), (override));
private:
};

class TestableExitActor : public iExit
{
public:
	void doExit() override
	{
		cout << "Testable Exit" << endl;
	}
private:
};

class ShellTestFixture : public Test
{
protected:
	//NiceMock<SsdMock> ssdMock{};
	NiceMock<SsdExcutalbeMock> ssdExecutableMock{};
	Shell shell{ &ssdExecutableMock };
	TestableExitActor testableExitActor;

	static constexpr int INVALID_LBA = 100;
	static constexpr int VALID_LBA = 99;
	const string dataZero = "0x00000000";

	void SetUp(void) override
	{
		shell.setExit(&testableExitActor);
	}
	void redirectCout(ostringstream& redirectedOutput)
	{
		reservedCout = cout.rdbuf(redirectedOutput.rdbuf());
	}
	void restoreCout(void)
	{
		cout.rdbuf(reservedCout);
	}
private:
	streambuf* reservedCout;
};

TEST_F(ShellTestFixture, HelpCallTest)
{
	ostringstream redirectedOutput;
	redirectCout(redirectedOutput);
	shell.help();
	restoreCout();

	ostringstream expectedOutput;
	redirectCout(expectedOutput);
	shell.helpMessasge();
	restoreCout();

	EXPECT_EQ(redirectedOutput.str(), expectedOutput.str());
}

TEST_F(ShellTestFixture, ExitCallTest)
{

	ostringstream redirectedOutput;
	redirectCout(redirectedOutput);
	shell.exit();
	restoreCout();

	ostringstream expectedOutput;
	redirectCout(expectedOutput);
	testableExitActor.doExit();
	restoreCout();

	EXPECT_EQ(redirectedOutput.str(), expectedOutput.str());
}

TEST_F(ShellTestFixture, OutOfLbaRead)
{
	EXPECT_CALL(ssdExecutableMock, execute(_)).Times(0);

	EXPECT_EQ("Out of Lba", shell.read(INVALID_LBA));
}

TEST_F(ShellTestFixture, ReadSuccess)
{
	EXPECT_CALL(ssdExecutableMock, execute(_)).Times(100);
	ostringstream redirectedOutput;
	redirectCout(redirectedOutput);

	for (int lba = 0; lba < 100; lba++)
	{
		EXPECT_EQ("0x00000000", shell.read(lba));
	}
	restoreCout();
}

TEST_F(ShellTestFixture, OutOfLbaWrite)
{
	EXPECT_CALL(ssdExecutableMock, execute(_)).Times(0);
	shell.write(INVALID_LBA, dataZero);
}

TEST_F(ShellTestFixture, InvalidDataFormatWrite)
{
	EXPECT_CALL(ssdExecutableMock, execute(_)).Times(0);
	shell.write(VALID_LBA, "0x0");
}

TEST_F(ShellTestFixture, WriteSuccess)
{
	EXPECT_CALL(ssdExecutableMock, execute(_)).Times(1);
	shell.write(VALID_LBA, dataZero);
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