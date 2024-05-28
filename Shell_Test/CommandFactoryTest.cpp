#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Shell/CommandFactory.cpp"
#include "SsdMock.h"

using namespace testing;

class CommandFactoryTest : public Test
{
public:
	
};

TEST_F(CommandFactoryTest, ConstructorAndCreate)
{
	NiceMock<SsdExcutalbeMock> ssdExecutableMock{};
	NiceMock<SsdResultMock> ssdResultMock{};
	SsdHelper ssd{ &ssdExecutableMock, &ssdResultMock };
	CommandFactory factory{std::cout, ssd };

	EXPECT_NE(nullptr, factory.create("read"));
	EXPECT_NE(nullptr, factory.create("write"));
	EXPECT_NE(nullptr, factory.create("fullread"));
	EXPECT_NE(nullptr, factory.create("fullwrite"));
	EXPECT_NE(nullptr, factory.create("erase"));
	EXPECT_NE(nullptr, factory.create("erase_range"));
	EXPECT_NE(nullptr, factory.create("exit"));
	EXPECT_EQ(nullptr, factory.create("INVALID"));
}