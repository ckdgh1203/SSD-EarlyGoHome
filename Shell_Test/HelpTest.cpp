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
    Help help{m_redirectedOutput, ssd, &factory};
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
        "\thelp\n"
        "\texit\n";
    EXPECT_EQ(expectedMessage, commandOutput);
}
