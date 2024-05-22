#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>

#include "../Shell/Shell.cpp"
#include "../SSD/iSSD.h"

using namespace std;
using namespace testing;

class SsdMock : public iSSD
{
public:
	MOCK_METHOD(void, write, (int, string), (override));
	MOCK_METHOD(void, read, (int), (override));
private:
};

class ShellTestFixture : public Test
{
public:
	NiceMock<SsdMock> ssdMock{};
	Shell shell{ &ssdMock };
protected:
	static constexpr int INVALID_LBA = 100;
	static constexpr int VALID_LBA = 99;
	const string dataZero = "0x00000000";
};

class TestableExitActor : public iExit
{
public:
	void doExit() override 
	{
		cout << "Tesable Exit" << endl;
	}
private:
};

TEST_F(ShellTestFixture, HelpCallTest)
{
	Shell shell;
	ostringstream redirectedOutput;
	ostringstream expectedOutput;
	streambuf* oldCout;

	oldCout = cout.rdbuf(redirectedOutput.rdbuf());
	shell.help();
	cout.rdbuf(oldCout);

	oldCout = cout.rdbuf(expectedOutput.rdbuf());
	shell.helpMessasge();
	cout.rdbuf(oldCout);

	EXPECT_EQ(redirectedOutput.str(), expectedOutput.str());
}

TEST_F(ShellTestFixture, DISABLE_ExitCallTest)
{
	Shell shell;
	TestableExitActor testableExitActor;

	ostringstream redirectedOutput;
	ostringstream expectedOutput;
	streambuf* oldCout;

	shell.setExit(&testableExitActor);

	oldCout = cout.rdbuf(redirectedOutput.rdbuf());
	shell.exit();
	cout.rdbuf(oldCout);

	oldCout = cout.rdbuf(expectedOutput.rdbuf());
	testableExitActor.doExit();
	cout.rdbuf(oldCout);

	EXPECT_EQ(redirectedOutput.str(), expectedOutput.str());
}

TEST_F(ShellTestFixture, OutOfLbaRead)
{
	EXPECT_CALL(ssdMock, read(_)).Times(0);
	EXPECT_EQ("Out of Lba", shell.read(INVALID_LBA));
}

TEST_F(ShellTestFixture, ReadSuccess)
{
	EXPECT_CALL(ssdMock, read(_)).Times(100);

	for (int lba = 0; lba < 100; lba++)
	{
		EXPECT_EQ("0x00000000", shell.read(lba));
	}
}

TEST_F(ShellTestFixture, OutOfLbaWrite)
{
	EXPECT_CALL(ssdMock, write(_, _)).Times(0);
	shell.write(INVALID_LBA, dataZero);
}

TEST_F(ShellTestFixture, InvalidDataFormatWrite)
{
	EXPECT_CALL(ssdMock, write(_, _)).Times(0);
	shell.write(VALID_LBA, "0x0");
}

TEST_F(ShellTestFixture, WriteSuccess)
{
	EXPECT_CALL(ssdMock, write(_, _)).Times(1);
	shell.write(VALID_LBA, dataZero);
}

TEST_F(ShellTestFixture, RunAndExit)
{
	Shell shell;
	TestableExitActor testableExitActor;
	shell.setExit(&testableExitActor);

	istringstream redirectedInput("exit\n");
	streambuf* oldCin;
	oldCin = cin.rdbuf(redirectedInput.rdbuf());
	shell.run();
	cout.rdbuf(oldCin);
}