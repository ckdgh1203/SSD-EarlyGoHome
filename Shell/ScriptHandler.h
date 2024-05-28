#pragma once

#include "CommandFactory.h"
#include "SsdHelper.h"
#include <sstream>

using namespace std;

class ScriptHandler
{
public:
    ScriptHandler(ostringstream& stringStream, SsdHelper& ssdHelper);

    virtual void doScript() = 0;

protected:
    CommandFactory m_CommandFactory;
    ostringstream& m_stringStream;

    void clearOutputStreamBuffer();
    bool readCompare(const string& inputData, unsigned int startLba, unsigned int endLba);
    void readRepeatedly(unsigned int startLba, unsigned int endLba);
    void writeRepeatedly(const string& inputData, unsigned int startLba, unsigned int endLba);
    void doFullWrite(const string& inputData);
    void duFullRead();
};