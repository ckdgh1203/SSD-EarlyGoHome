#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

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

class TestableExitActor : public iExit
{
public:
	void doExit() override
	{
		cout << "Tesable Exit" << endl;
	}
private:
};

class ShellTestFixture : public Test
{
protected:
	NiceMock<SsdMock> ssdMock{};
	Shell shell{ &ssdMock };
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
	void redirectCin(istringstream& redirectedInput)
	{
		reservedCin = cin.rdbuf(redirectedInput.rdbuf());
	}
	void restoreCin(void)
	{
		cin.rdbuf(reservedCin);
	}
private:
	streambuf* reservedCout;
	streambuf* reservedCin;
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

TEST_F(ShellTestFixture, DISABLE_ExitCallTest)
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
	istringstream redirectedInput("exit\n");
	redirectCin(redirectedInput);
	shell.run();
	restoreCin();
}