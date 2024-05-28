#pragma once

#include "SsdHelper.h"
#include "CommandFactory.h"
#include "ScriptFactory.h"
#include "Help.h"
#include <iostream>
#include <vector>

using namespace std;

class Shell
{
public:

    Shell(SsdHelper& _ssd, ostream& _out);

    void run(istream& inputStream);
    void runRunner(const string& fileName);
    void parseArguments(istream& inputStream, vector<string>& args);

private:
    ostream& m_outputStream;
    SsdHelper& m_ssdHelper;
    CommandFactory m_commandFactory;
    ScriptFactory m_scriptFactory;
    Help m_help;
    string getDirectoryPath(string filePath);
};