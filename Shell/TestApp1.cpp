#pragma once

#include "ScriptHandler.cpp"

class TestApp1 : public ScriptHandler
{
public:
	TestApp1(CommandFactory& commandFactory, ostream& outputStream)
		: ScriptHandler(commandFactory, outputStream)
	{

	}
	// ScriptHandler을(를) 통해 상속됨
    void doScript() override
    {
		doFullWrite("0xDEADC0DE");
		doFullRead();

		bool isCompareSuccess = readCompare("0xDEADC0DE", 100);

		if (false == isCompareSuccess)
		{
			m_outputStream << "[WARNING] testapp1 : written data is different with read data!!!" << endl;
			return;
		}

		m_outputStream << "testapp1 : Done test, written data is same with read data :)" << endl;
	}
};