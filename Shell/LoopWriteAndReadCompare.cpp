#pragma once

#include "ScriptHandler.cpp"

class LoopWriteAndReadCompare : public ScriptHandler
{
public:
	LoopWriteAndReadCompare(CommandFactory& commandFactory, ostream& outputStream)
		: ScriptHandler(commandFactory, outputStream)
	{

	}

	// ScriptHandler을(를) 통해 상속됨
	void doScript() override
	{/*
		for (int iter = 0; iter < 10; iter++)
		{
			writeRepeatedly("0xDEADC0DE", 10);
		}

		readRepeatedly(10);
		bool compareResult = readCompare("0xDEADC0DE", 10);
		*/
	}
};