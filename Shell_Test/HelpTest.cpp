#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Shell/Help.cpp"
#include "SsdMock.h"
#include "OutputCapture.h"

using namespace testing;

class HelpTest : public Test, public OutputCapture
{
public:
    NiceMock<SsdExcutalbeMock> ssdExecutableMock{};
    NiceMock<SsdResultMock> ssdResultMock{};
    SsdHelper ssd{ &ssdExecutableMock, &ssdResultMock };
    CommandFactory factory{ std::cout, ssd };
    ScriptFactory scriptFactory{};
    Help help{m_redirectedOutput, ssd, &factory, &scriptFactory};
};

TEST_F(HelpTest, DoCommand)
{
	vector<string> emptyArgs;
	EXPECT_EQ(Progress::Continue, help.doCommand(emptyArgs));
    auto commandOutput = fetchOutput();
    const string expectedMessage = "Help:\n"
        "\tread [LBA]\n"
        "\twrite [LBA] [DATA]\n"
        "\tfullread\n"
        "\tfullwrite [DATA]\n"
        "\terase [START_LBA] [NUMBER_OF_LBA]\n"
        "\terase_range [START_LBA] [END_LBA]\n"
        "\texit\n"
        "\ttestapp1 or FullWriteAndFullReadAndCompare\n"
        "\ttestapp2 or Write0to6Repeat30AndWrite0to6AndReadCompare\n"
        "\ttestapp3 or FullWriteAndRead99AndCompare\n"
        "\ttestapp4 or FullReadAndCompare\n"
        "\ttestapp5 or Write0Repeat10AndReadCompare\n"
        "\ttestapp6 or Write5to10AndWrite8to10AndReadCompare\n"
        "\thelp\n";
    EXPECT_EQ(expectedMessage, commandOutput);
}
