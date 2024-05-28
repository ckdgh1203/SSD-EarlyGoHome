#pragma once

#include "ScriptHandler.cpp"

class TestApp2 : public ScriptHandler
{
public:
    TestApp2(ostringstream& stringStream, SsdHelper& ssdHelper)
        : ScriptHandler(stringStream, ssdHelper)
    {

    }

	bool doScript() override
	{
        unsigned int startLba = 0;
        unsigned int endLba = 6;

        for (int iter = 0; iter < 30; iter++)
        {
            writeRepeatedly("0xAAAABBBB", startLba, endLba);
        }

        writeRepeatedly("0x12345678", startLba, endLba);
        readRepeatedly(startLba, endLba);

        string referenceData = createReferenceData("0x12345678", (endLba - startLba));
        bool isCompareSuccess = readCompare(referenceData, startLba, endLba);

        if (false == isCompareSuccess)
        {
            return false;
        }

        return true;
	}
};