#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>

#include "../SSD/iSSD.h"
#include "../Shell/Shell.cpp"

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