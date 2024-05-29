#pragma once

#include <string>
#include <sstream>

class OutputCapture
{
protected:
    std::string fetchOutput(void)
    {
        auto fetchedString = m_redirectedOutput.str();
        m_redirectedOutput.str("");
        m_redirectedOutput.clear();
        return fetchedString;
    }
    std::ostringstream m_redirectedOutput{};
};
