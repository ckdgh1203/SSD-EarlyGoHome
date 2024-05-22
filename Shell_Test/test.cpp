#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>

using namespace std;
using namespace testing;

class SsdMock
{
	MOCK_METHOD(void, Write, (unsigned int, unsigned int), ());
	MOCK_METHOD(void, Read, (unsigned int), ());
};

class ShellTest : public Test
{
	NiceMock<SsdMock> ssdMock{};
};

TEST_F(ShellTest, InvalidCommand)
{

}

TEST_F(ShellTest, InvalidFormat)
{

}

TEST_F(ShellTest, LBAOutOfBound)
{

}

TEST_F(ShellTest, WriteInvalidData)
{

}

TEST_F(ShellTest, WriteCommandSuccess)
{

}

TEST_F(ShellTest, WriteCommandFailure)
{

}

TEST_F(ShellTest, ReadCommandSuccess)
{

}

TEST_F(ShellTest, ReadCommandFailure)
{

}

TEST_F(ShellTest, ExitCommandSuccess)
{

}