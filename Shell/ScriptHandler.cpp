#pragma once

#include <iostream>
#include <sstream>
#include "CommandFactory.cpp"

using namespace std;

class ScriptHandler
{
public:
    ScriptHandler(CommandFactory& commandFactory, ostream& outputStream)
        : m_CommandFactory(commandFactory), m_outputStream(outputStream)
    {

    }

    virtual void doScript() = 0;

protected:
    CommandFactory& m_CommandFactory;
    ostream& m_outputStream;

    bool readCompare(const string& inputData, unsigned int lbaBound)
    {
        string referenceData = "";
        for (int iter = 0; iter < lbaBound; iter++)
        {
            referenceData += inputData;
        }

        ostringstream* redirectedOutput = dynamic_cast<ostringstream*>(&m_outputStream);
        string readData = redirectedOutput->str();
        redirectedOutput->str("");
        redirectedOutput->clear();

        return (referenceData == readData);
    }

    void readRepeatedly(const int lbaBound)
    {
        CommandHandler* readCommand = m_CommandFactory.create("read");
        for (int lbaIter = 0; lbaIter < lbaBound; lbaIter++)
        {
            readCommand->doCommand(lbaIter);
        }
    }

    void writeRepeatedly(const string& inputData, const int lbaBound)
    {
        for (int lbaIter = 0; lbaIter < lbaBound; lbaIter++)
        {
            write(lbaIter, inputData);
        }
    }
};