#pragma once

#include "ScriptHandler.cpp"

class TestApp1 : public ScriptHandler
{
public:
    // ScriptHandler을(를) 통해 상속됨
    void doScript() override
    {
		vector<string> fullwriteArgument;
		fullwriteArgument.push_back({ "fullwrite","0xDEADC0DE" });

		CommandHandler* fullwriteCmd = m_CommandFactory.create("fullwrite");
		fullwriteCmd->isValidArgs(fullwriteArgument);
		fullwriteCmd->doCommand(fullwriteArgument);

		vector<string> fullreadArgument;
		fullreadArgument.push_back("fullread");

		CommandHandler* fullreadCmd = m_CommandFactory.create("fullread");
		fullreadCmd->isValidArgs(fullreadArgument);
		fullreadCmd->doCommand(fullreadArgument);

		bool isCompareSuccess = readCompare("0xDEADC0DE", 100);

		if (false == isCompareSuccess)
		{
			m_outputStream << "[WARNING] testapp1 : written data is different with read data!!!" << endl;
			return;
		}

		m_outputStream << "testapp1 : Done test, written data is same with read data :)" << endl;
	}
};