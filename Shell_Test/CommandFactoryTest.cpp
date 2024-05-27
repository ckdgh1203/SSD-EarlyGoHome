#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Shell/CommandFactory.cpp"

using namespace testing;

class CommandFactoryTest : public Test
{
public:
	
};

TEST_F(CommandFactoryTest, ConstructorAndCreate)
{
	CommandFactory factory{};
	EXPECT_NE(nullptr, factory.create("read"));
	EXPECT_NE(nullptr, factory.create("write"));
	EXPECT_NE(nullptr, factory.create("fullread"));
	EXPECT_NE(nullptr, factory.create("fullwrite"));
	EXPECT_NE(nullptr, factory.create("help"));
	EXPECT_NE(nullptr, factory.create("exit"));
	EXPECT_EQ(nullptr, factory.create("INVALID"));
}