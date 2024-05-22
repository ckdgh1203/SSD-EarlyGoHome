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
};

class ShellTest : public Test
{
public:
	NiceMock<SsdMock> ssdMock{};
	Shell shell{ &ssdMock };
};

TEST_F(ShellTest, OutOfLbaRead)
{
	constexpr int TEST_LBA = 100;
	EXPECT_CALL(ssdMock, read(_)).Times(0);
	EXPECT_EQ("Out of Lba", shell.read(TEST_LBA));
}

TEST_F(ShellTest, ReadSuccess)
{
	EXPECT_CALL(ssdMock, read(_)).Times(100);

	for (int lba = 0; lba < 100; lba++)
	{
		EXPECT_EQ("0x00000000", shell.read(lba));
	}
}

TEST_F(ShellTest, OutOfLbaWrite)
{
	constexpr int INVALID_LBA = 100;
	const string dataZero = "0x00000000";
	EXPECT_CALL(ssdMock, write(_, _)).Times(0);
	shell.write(INVALID_LBA, dataZero);
}

TEST_F(ShellTest, InvalidDataFormatWrite)
{
	constexpr int VALID_LBA = 99;

	EXPECT_CALL(ssdMock, write(_, _)).Times(0);
	shell.write(VALID_LBA, "0x0");
}

TEST_F(ShellTest, WriteSuccess)
{
	constexpr int VALID_LBA = 99;
	const string dataZero = "0x00000000";

	EXPECT_CALL(ssdMock, write(_, _)).Times(1);
	shell.write(VALID_LBA, dataZero);
}
