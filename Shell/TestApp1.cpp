#include "TestApp1.h"

bool TestApp1::doScript()
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
