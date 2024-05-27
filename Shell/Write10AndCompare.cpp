#pragma once

#include "ScriptHandler.cpp"

class Write10AndCompare : public ScriptHandler
{
public:
	Write10AndCompare(CommandFactory& commandFactory, ostream& outputStream)
		: ScriptHandler(commandFactory, outputStream)
	{

	}

	// ScriptHandler을(를) 통해 상속됨
	void doScript() override
	{/*
		for (int iter = 0; iter < 10; iter++)
		{
			writeRepeatedly("0xDEADC0DE", 1);
		}

		readRepeatedly(1);
		bool compareResult = readCompare("0xDEADC0DE", 1);
		*/
	}
};