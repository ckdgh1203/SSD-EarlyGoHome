#pragma once

#include "ScriptHandler.cpp"

class TestApp2 : public ScriptHandler
{
public:
    TestApp2(CommandFactory& commandFactory, ostream& outputStream)
        : ScriptHandler(commandFactory, outputStream)
    {

    }

	// ScriptHandler을(를) 통해 상속됨
	void doScript() override
	{
        unsigned int lbaBound = 6;

        for (int i = 0; i < 30; i++)
        {
            writeRepeatedly("0xAAAABBBB", lbaBound);
        }

        writeRepeatedly("0x12345678", lbaBound);
        readRepeatedly(lbaBound);

        bool isCompareSuccess = readCompare("0x12345678", lbaBound);

        if (false == isCompareSuccess)
        {
            m_outputStream << "[WARNING] testapp2 : written data is different with read data!!!" << endl;
            return;
        }
        m_outputStream << "testapp2 : Done test, written data is same with read data :)" << endl;
	}
};