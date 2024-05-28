#include "TestApp2.h"

bool TestApp2::doScript()
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
