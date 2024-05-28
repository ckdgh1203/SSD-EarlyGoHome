#pragma once

#include "SsdHelper.h"
#include "CommandFactory.h"
#include "ScriptFactory.h"

#include <iostream>
#include <vector>

using namespace std;

class Shell
{
public:

    Shell(SsdHelper& _ssd, ostream& _out) :
        m_ssdHelper(_ssd),
        m_commandFactory(_out, _ssd),
        m_outputStream(_out)
    {}

    void run(istream& inputStream);
    void parseArguments(istream& inputStream, vector<string>& args);

private:
    ostream& m_outputStream;
    SsdHelper& m_ssdHelper;
    CommandFactory m_commandFactory;
    ScriptFactory m_scriptFactory;
};