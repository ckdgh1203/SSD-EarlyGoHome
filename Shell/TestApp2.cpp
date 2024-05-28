#pragma once

#include "ScriptHandler.cpp"

class TestApp2 : public ScriptHandler
{
public:
    TestApp2(ostringstream& stringStream, SsdHelper& ssdHelper)
        : ScriptHandler(stringStream, ssdHelper)
    {

    }

	void doScript() override
	{
        unsigned int startLba = 0;
        unsigned int endLba = 6;

        for (int iter = 0; iter < 30; iter++)
        {
            writeRepeatedly("0xAAAABBBB", startLba, endLba);
        }

        writeRepeatedly("0x12345678", startLba, endLba);
        readRepeatedly(startLba, endLba);

        bool isCompareSuccess = readCompare("0x12345678", startLba, endLba);

        if (false == isCompareSuccess)
        {
            m_stringStream << "[WARNING] testapp2 : written data is different with read data!!!" << endl;
            cout << m_stringStream.str();
            return;
        }
        m_stringStream << "testapp2 : Done test, written data is same with read data :)" << endl;
        cout << m_stringStream.str();
	}
};