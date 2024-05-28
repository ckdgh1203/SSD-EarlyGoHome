#include "ScriptHandler.h"

ScriptHandler::ScriptHandler(ostringstream& stringStream, SsdHelper& ssdHelper)
    : m_CommandFactory(stringStream, ssdHelper), m_stringStream(stringStream)
{
    clearOutputStreamBuffer();
}

void ScriptHandler::clearOutputStreamBuffer()
{
    m_stringStream.str("");
    m_stringStream.clear();
}

bool ScriptHandler::readCompare(const string& inputData, unsigned int startLba, unsigned int endLba)
{
    string referenceData = "";
    for (unsigned int iter = startLba; iter < endLba; iter++)
    {
        referenceData += (inputData + "\n");
    }

    string readData = m_stringStream.str();
    clearOutputStreamBuffer();

    return (readData == referenceData);
}

void ScriptHandler::readRepeatedly(unsigned int startLba, unsigned int endLba)
{
    vector<vector<string>> argument;
    for (unsigned int lbaIter = startLba; lbaIter < endLba; lbaIter++)
    {
        argument.push_back({ "read", to_string(lbaIter) });
    }

    CommandHandler* readCommand = m_CommandFactory.create("read");
    for (unsigned int lbaIter = startLba; lbaIter < endLba; lbaIter++)
    {
        readCommand->doCommand(argument[lbaIter]);
    }
}

void ScriptHandler::writeRepeatedly(const string& inputData, unsigned int startLba, unsigned int endLba)
{
    vector<vector<string>> argument;
    for (unsigned int lbaIter = startLba; lbaIter < endLba; lbaIter++)
    {
        argument.push_back({ "write", to_string(lbaIter), inputData });
    }

    CommandHandler* writeCommand = m_CommandFactory.create("write");
    for (unsigned int lbaIter = startLba; lbaIter < endLba; lbaIter++)
    {
        writeCommand->doCommand(argument[lbaIter]);
    }
}

void ScriptHandler::doFullWrite(const string& inputData)
{
    vector<string> fullwriteArgument;
    fullwriteArgument.push_back("fullwrite");
    fullwriteArgument.push_back(inputData);

    CommandHandler* fullwriteCmd = m_CommandFactory.create("fullwrite");
    fullwriteCmd->isValidArgs(fullwriteArgument);
    fullwriteCmd->doCommand(fullwriteArgument);
}

void ScriptHandler::duFullRead()
{
    vector<string> fullreadArgument;
    fullreadArgument.push_back("fullread");

    CommandHandler* fullreadCmd = m_CommandFactory.create("fullread");
    fullreadCmd->isValidArgs(fullreadArgument);
    fullreadCmd->doCommand(fullreadArgument);
}
