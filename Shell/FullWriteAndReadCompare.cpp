#pragma once

#include "ScriptHandler.cpp"

class FullWriteAndReadCompare : public ScriptHandler
{
public:
	FullWriteAndReadCompare(CommandFactory& commandFactory, ostream& outputStream)
		: ScriptHandler(commandFactory, outputStream)
	{

	}

	// ScriptHandler을(를) 통해 상속됨
	void doScript() override
	{
		/*doFullWrite("0xDEADC0DE");
		bool compareResult = readCompare("0xDEADC0DE", 100);*/
	}
};