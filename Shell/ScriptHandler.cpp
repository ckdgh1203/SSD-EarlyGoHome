#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include "CommandFactory.cpp"

using namespace std;

class ScriptHandler
{
public:
    ScriptHandler(ostringstream& stringStream, SsdHelper& ssdHelper)
        : m_CommandFactory(stringStream, ssdHelper), m_stringStream(stringStream)
    {
        clearOutputStreamBuffer();
    }

    virtual bool doScript() = 0;

protected:
    CommandFactory m_CommandFactory;
    ostringstream& m_stringStream;
    
    string createReferenceData(const string& inputData, const int iteration)
    {
        string Data = "";
        for (int iter = 0; iter < iteration; iter++)
        {
            Data += (inputData + "\n");
        }

        return Data;
    }

    void clearOutputStreamBuffer()
    {
        m_stringStream.str("");
        m_stringStream.clear();
    }

    bool readCompare(const string& inputData, unsigned int startLba, unsigned int endLba)
    {
        string readData = m_stringStream.str();
        clearOutputStreamBuffer();

        return (readData == inputData);
    }

    void readRepeatedly(unsigned int startLba, unsigned int endLba)
    {
        vector<vector<string>> argument;
        for (unsigned int lbaIter = startLba; lbaIter < endLba; lbaIter++)
        {
            argument.push_back({ "read", to_string(lbaIter) });
        }

        CommandHandler* readCommand = m_CommandFactory.create("read");
        for (unsigned int Iter = 0; Iter < (endLba - startLba); Iter++)
        {
            readCommand->doCommand(argument[Iter]);
        }
    }

    void writeRepeatedly(const string& inputData, unsigned int startLba, unsigned int endLba)
    {
        vector<vector<string>> argument;
        for (unsigned int lbaIter = startLba; lbaIter < endLba; lbaIter++)
        {
            argument.push_back({ "write", to_string(lbaIter), inputData });
        }

        CommandHandler* writeCommand = m_CommandFactory.create("write");
        for (unsigned int Iter = 0; Iter < (endLba - startLba); Iter++)
        {
            writeCommand->doCommand(argument[Iter]);
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

    void doFullRead()
    {
        vector<string> fullreadArgument;
        fullreadArgument.push_back("fullread");

        CommandHandler* fullreadCmd = m_CommandFactory.create("fullread");
        fullreadCmd->isValidArgs(fullreadArgument);
        fullreadCmd->doCommand(fullreadArgument);
    }
};