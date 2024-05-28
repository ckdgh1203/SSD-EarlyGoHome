#pragma once

#include "SsdExcutable.h"
#include "SsdResult.h"

class SsdHelper
{
public:
    SsdHelper(ISsdExecutable* executable, ISsdResult* result) :
        m_ssdExcutable(executable), m_ssdResult(result)
    {
        m_ssdExcutable->execute("G");
        m_ssdResult->setResultFilePath(m_ssdExcutable->getResultFilePath());
    }
    bool execute(const string& arguments)
    {
        return m_ssdExcutable->execute(arguments);
    }
    string getResult(void)
    {
        return m_ssdResult->get();
    }
private:
    ISsdExecutable* m_ssdExcutable{};
    ISsdResult* m_ssdResult{};
};
