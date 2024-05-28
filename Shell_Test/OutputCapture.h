#pragma once

#include <string>
#include <sstream>

class OutputCapture
{
protected:
    std::string fetchOutput(void)
    {
        auto fetchedString = redirectedOutput.str();
        redirectedOutput.str("");
        redirectedOutput.clear();
        return fetchedString;
    }
    std::ostringstream redirectedOutput{};
};
