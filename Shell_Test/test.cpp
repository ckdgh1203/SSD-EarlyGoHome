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
	MOCK_METHOD(void, Write, (int, string), ());
	MOCK_METHOD(void, Read, (int), ());
};

class ShellTest : public Test
{
	NiceMock<SsdMock> ssdMock{};
};

TEST_F(ShellTest, Test)
{

}