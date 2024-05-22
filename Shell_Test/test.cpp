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
	MOCK_METHOD(void, write, (int, string), (override));
	MOCK_METHOD(void, read, (int), (override));
};

class ShellTest : public Test
{
public:
	NiceMock<SsdMock> ssdMock{};
	Shell shell{ &ssdMock };
};

TEST_F(ShellTest, OutOfLba)
{
	constexpr int TEST_LBA = 100;
	EXPECT_EQ("Out of Lba", shell.read(TEST_LBA));
}

TEST_F(ShellTest, VerifyCommand)
{

}

TEST_F(ShellTest, InvalidDataFormatRead)
{

}

TEST_F(ShellTest, ReadSuccess)
{

}

TEST_F(ShellTest, InvalidDataFormatWrite)
{

}

TEST_F(ShellTest, WriteSuccess)
{

}
