#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Shell/Help.cpp"
#include "SsdMock.h"

using namespace testing;

class HelpTest : public Test
{
public:
    class TestableHelp : public Help
    {
    public:
        NiceMock<SsdExcutalbeMock> ssdExecutableMock{};
        NiceMock<SsdResultMock> ssdResultMock{};
        SsdHelper ssd{ &ssdExecutableMock, &ssdResultMock };
        TestableHelp(ostream& _out) : Help(_out, ssd) {}
        const string& helpMessage(void)
        {
            return m_helpMessage;
        }
    };
    TestableHelp help{ redirectedOutput };

    string fetchOutput(void)
    {
        auto fetchedString = redirectedOutput.str();
        redirectedOutput.str("");
        redirectedOutput.clear();
        return fetchedString;
    }

private:
    ostringstream redirectedOutput{};
};

TEST_F(HelpTest, DoCommand)
{
	vector<string> emptyArgs;
	EXPECT_EQ(Progress::Continue, help.doCommand(emptyArgs));
    auto commandOutput = fetchOutput();

    EXPECT_EQ(help.helpMessage(), commandOutput);
}
