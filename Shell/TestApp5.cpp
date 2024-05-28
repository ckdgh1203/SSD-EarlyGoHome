#pragma once

#include "ScriptHandler.cpp"

class TestApp5 : public ScriptHandler
{
public:
	TestApp5(ostringstream& stringStream, SsdHelper& ssdHelper)
		: ScriptHandler(stringStream, ssdHelper)
	{

	}

	bool doScript() override
	{
		unsigned int startLba = 0;
		unsigned int endLba = 1;

		for (int iter = 0; iter < 10; iter++)
		{
			writeRepeatedly("0xDEADC0DE", startLba, endLba);
		}

		readRepeatedly(startLba, endLba);

		string referenceData = createReferenceData("0xDEADC0DE", (endLba - startLba));
		return readCompare(referenceData, startLba, endLba);
	}
};