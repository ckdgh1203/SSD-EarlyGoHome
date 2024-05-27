#pragma once

#include "ScriptHandler.cpp"

class FullRead10AndCompare : public ScriptHandler
{
public:
	FullRead10AndCompare(CommandFactory& commandFactory, ostream& outputStream)
		: ScriptHandler(commandFactory, outputStream)
	{

	}

	// ScriptHandler을(를) 통해 상속됨
	void doScript() override
	{/*
		ostringstream* redirectedOutput = dynamic_cast<ostringstream*>(&m_outputStream);
		redirectedOutput->str("");
		redirectedOutput->clear();

		for (int iter = 0; iter < 10; iter++)
		{
			doFullRead();

			string expectedData;
			if (iter == 0)
			{
				expectedData = redirectedOutput->str();
				continue;
			}

			if (expectedData == redirectedOutput->str())
			{
				cout << " Good Result ";
			}
			else
			{
				cout << " Bad Result ";
			}

			redirectedOutput->str("");
			redirectedOutput->clear();
		}*/
	}
};