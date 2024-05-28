#include "ScriptHandler.h"

ScriptHandler::ScriptHandler(ostringstream& stringStream, SsdHelper& ssdHelper)
    : m_CommandFactory(stringStream, ssdHelper), m_stringStream(stringStream)
{
    clearOutputStreamBuffer();
}

string ScriptHandler::getScriptResult()
{
    if (false == this->doScript()) return "Fail!\n";

    return "Pass!\n";
}

void ScriptHandler::clearOutputStreamBuffer()
{
    m_stringStream.str("");
    m_stringStream.clear();
}

string ScriptHandler::createReferenceData(const string& inputData, const int iteration)
{
    string Data = "";
    for (int iter = 0; iter < iteration; iter++)
    {
        Data += (inputData + "\n");
    }

    return Data;
}

bool ScriptHandler::readCompare(const string& inputData, unsigned int startLba, unsigned int endLba)
{
    string readData = m_stringStream.str();
    clearOutputStreamBuffer();

    return (readData == inputData);
}

void ScriptHandler::readRepeatedly(unsigned int startLba, unsigned int endLba)
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

void ScriptHandler::writeRepeatedly(const string& inputData, unsigned int startLba, unsigned int endLba)
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

void ScriptHandler::doFullWrite(const string& inputData)
{
    vector<string> fullwriteArgument;
    fullwriteArgument.push_back("fullwrite");
    fullwriteArgument.push_back(inputData);

    CommandHandler* fullwriteCmd = m_CommandFactory.create("fullwrite");
    fullwriteCmd->isValidArgs(fullwriteArgument);
    fullwriteCmd->doCommand(fullwriteArgument);
}

void ScriptHandler::doFullRead()
{
    vector<string> fullreadArgument;
    fullreadArgument.push_back("fullread");

    CommandHandler* fullreadCmd = m_CommandFactory.create("fullread");
    fullreadCmd->isValidArgs(fullreadArgument);
    fullreadCmd->doCommand(fullreadArgument);
}
