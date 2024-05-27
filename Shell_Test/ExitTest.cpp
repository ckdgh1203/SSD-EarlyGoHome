#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Shell/Exit.cpp"

using namespace testing;

class ExitTest : public Test
{
public:
	Exit exit{std::cout};
};

TEST_F(ExitTest, ConstructorAndCreate)
{
	vector<string> emptyArgs;
	EXPECT_EQ(Progress::Done, exit.doCommand(emptyArgs));
}