#include "gtest/gtest.h"
#include "gmock/gmock.h"
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
};

class ShellTest : public Test
{
public:
	NiceMock<SsdMock> ssdMock{};
};

TEST_F(ShellTest, FullWrite_NotIncludedPrefixException)
{
	Shell shell(&ssdMock);
	string inputData = "abcd1234";

	EXPECT_THROW(shell.fullwrite(inputData), NotIncludedPrefix);
}

TEST_F(ShellTest, FullWrite_NotAllowedInputDataException)
{
	Shell shell(&ssdMock);
	string inputData = "0xabcd1234";

	EXPECT_THROW(shell.fullwrite(inputData), NotAllowedInputData);
}

TEST_F(ShellTest, FullWrite_100TimesSuccessfully)
{

}

TEST_F(ShellTest, FullWrite_Under100TimesException)
{

}

TEST_F(ShellTest, FullRead_100TimesSuccessfully)
{

}

TEST_F(ShellTest, FullRead_Under100TimesException)
{

}