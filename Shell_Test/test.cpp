#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>

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
	NiceMock<SsdMock> ssdMock{};
};

TEST_F(ShellTest, Test)
{

}