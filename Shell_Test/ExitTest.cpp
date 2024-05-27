#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Shell/Exit.cpp"
#include "TestableExitActor.h"

using namespace testing;

class ExitTest : public Test
{
public:
	Exit exit{};
};

TEST_F(ExitTest, ConstructorAndCreate)
{
	vector<string> emptyArgs;
	EXPECT_EQ(Progress::Done, exit.doCommand(emptyArgs));
}