#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Shell/Exit.cpp"
#include "SsdMock.h"

using namespace testing;

class ExitTest : public Test
{
public:
	NiceMock<SsdExcutalbeMock> ssdExecutableMock{};
	NiceMock<SsdResultMock> ssdResultMock{};
	SsdHelper ssd{ &ssdExecutableMock, &ssdResultMock };
	Exit exit{std::cout, ssd};
};

TEST_F(ExitTest, DoCommand)
{
	vector<string> emptyArgs;
	EXPECT_EQ(Progress::Done, exit.doCommand(emptyArgs));
}