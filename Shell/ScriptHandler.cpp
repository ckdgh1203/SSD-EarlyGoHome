#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include "CommandFactory.cpp"

using namespace std;

class ScriptHandler
{
public:
    ScriptHandler(CommandFactory& commandFactory, ostringstream& stringStream)
        : m_CommandFactory(commandFactory), m_stringStream(stringStream)
    {
        clearOutputStreamBuffer();
    }

    virtual void doScript() = 0;

protected:
    CommandFactory& m_CommandFactory;
    ostringstream& m_stringStream;

    void clearOutputStreamBuffer()
    {
        m_stringStream.str("");
        m_stringStream.clear();
    }

    bool readCompare(const string& inputData, unsigned int lbaBound)
    {
        string referenceData = "";
        for (unsigned int iter = 0; iter < lbaBound; iter++)
        {
            referenceData += (inputData + "\n");
        }

        string readData = m_stringStream.str();
        clearOutputStreamBuffer();

        return (readData == referenceData);
    }

    void readRepeatedly(const unsigned int lbaBound)
    {
        vector<vector<string>> argument;
        for (unsigned int lbaIter = 0; lbaIter < lbaBound; lbaIter++)
        {
            argument.push_back({ "read", to_string(lbaIter) });
        }

        CommandHandler* readCommand = m_CommandFactory.create("read");
        for (unsigned int lbaIter = 0; lbaIter < lbaBound; lbaIter++)
        {
            readCommand->doCommand(argument[lbaIter]);
        }
    }

    void writeRepeatedly(const string& inputData, const unsigned int lbaBound)
    {
        vector<vector<string>> argument;
        for (unsigned int lbaIter = 0; lbaIter < lbaBound; lbaIter++)
        {
            argument.push_back({ "write", to_string(lbaIter), inputData });
        }

        CommandHandler* writeCommand = m_CommandFactory.create("write");
        for (unsigned int lbaIter = 0; lbaIter < lbaBound; lbaIter++)
        {
            writeCommand->doCommand(argument[lbaIter]);
        }
    }

    void doFullWrite(const string& inputData)
    {
        vector<string> fullwriteArgument;
        fullwriteArgument.push_back("fullwrite");
        fullwriteArgument.push_back(inputData);

        CommandHandler* fullwriteCmd = m_CommandFactory.create("fullwrite");
        fullwriteCmd->isValidArgs(fullwriteArgument);
        fullwriteCmd->doCommand(fullwriteArgument);
    }

    void duFullRead()
    {
        vector<string> fullreadArgument;
        fullreadArgument.push_back("fullread");

        CommandHandler* fullreadCmd = m_CommandFactory.create("fullread");
        fullreadCmd->isValidArgs(fullreadArgument);
        fullreadCmd->doCommand(fullreadArgument);
    }
};