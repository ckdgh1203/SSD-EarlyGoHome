#pragma once

#include "ScriptHandler.cpp"

class TestApp3 : public ScriptHandler
{
public:
	TestApp3(ostringstream& stringStream, SsdHelper& ssdHelper)
		: ScriptHandler(stringStream, ssdHelper)
	{

	}

	bool doScript() override
	{
		doFullWrite("0xDEADC0DE");
		readRepeatedly(99, 100);

		string referenceData = createReferenceData("0xDEADC0DE", 1);
		return readCompare(referenceData, 99, 100);
	}
};