#pragma once

#include "ScriptHandler.cpp"

class TestApp1 : public ScriptHandler
{
public:
	TestApp1(ostringstream& stringStream, SsdHelper& ssdHelper)
		: ScriptHandler(stringStream, ssdHelper)
	{

	}

	bool doScript() override
    {
		doFullWrite("0xDEADC0DE");
		doFullRead();

		string referenceData = createReferenceData("0xDEADC0DE", 100);
		bool isCompareSuccess = readCompare(referenceData, 0, 100);

		if (false == isCompareSuccess)
		{
			return false;
		}
		
		return true;
	}
};