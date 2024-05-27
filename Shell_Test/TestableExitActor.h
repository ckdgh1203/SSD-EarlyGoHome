#pragma once
#include "../Shell/Exit.cpp"

class TestableExitActor : public iExit
{
public:
    TestableExitActor(ostream& _out) : m_outputStream(_out) {}
    bool isValidArgs(const vector<string>& args) override
    {
        return true;
    }
    void commandBody(const vector<string>& args) override
    {
        m_outputStream << "Testable Exit" << endl;
    }
    string defaultLogMsg() override
    {
        return "Testable Exit";
    }
    void doCommand()
    {
        m_outputStream << "Testable Exit" << endl;
    }
    void usage() override
    {
        m_outputStream << "Testable Exit Help Message" << endl;
    }
    void doExit() override
    {
        m_outputStream << "Testable Exit" << endl;
    }
    bool isTest() override
    {
        return true;
    }
private:
    ostream& m_outputStream;
};
