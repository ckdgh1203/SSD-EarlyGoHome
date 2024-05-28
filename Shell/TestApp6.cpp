#pragma once

#include "ScriptHandler.cpp"

class TestApp6 : public ScriptHandler
{
public:
	TestApp6(ostringstream& stringStream, SsdHelper& ssdHelper)
		: ScriptHandler(stringStream, ssdHelper)
	{

	}

	bool doScript() override
	{
		unsigned int trial1_startLba = 5;
		unsigned int endLba = 10;

		writeRepeatedly("0xDEADC0DE", trial1_startLba, endLba);

		unsigned int trial2_startLba = 8;
		writeRepeatedly("0x11111111", trial2_startLba, endLba);

		readRepeatedly(trial1_startLba, endLba);

		string referenceData = createReferenceData("0xDEADC0DE", (trial2_startLba - trial1_startLba));
		referenceData += createReferenceData("0x11111111", (endLba - trial2_startLba));
		return (readCompare(referenceData, trial1_startLba, endLba));
	}
};