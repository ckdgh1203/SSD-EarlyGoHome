#include "TestApp3.h"

bool TestApp3::doScript()
{
	doFullWrite("0xDEADC0DE");
	readRepeatedly(99, 100);

	string referenceData = createReferenceData("0xDEADC0DE", 1);
	return readCompare(referenceData, 99, 100);
}