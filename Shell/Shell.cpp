#include "../SSD/iSSD.h"
#include <string>
#include <stdexcept>

using namespace std;

class NotIncludedPrefix : public exception
{
public:
	NotIncludedPrefix()
		: exception("Prefix '0x' should be included!!!")
	{

	}
};

class NotAllowedInputData : public exception
{
public:
	NotAllowedInputData()
		: exception("InputData should be set to Capital characters or numbers")
	{

	}
};

class Shell
{
public:
	Shell(iSSD* ssd)
		: m_Ssd(ssd)
	{

	}

	void fullwrite(const string inputData)
	{
		if (inputData[0] != '0' || inputData[1] != 'x')
		{
			throw NotIncludedPrefix();
		}

		for (int index = 2; index < inputData.length(); index++)
		{
			if ((inputData[index] < 'A' || 'F' < inputData[index]) && (inputData[index] < '0' || '9' < inputData[index]))
			{
				throw NotAllowedInputData();
			}
		}
	}
private:
	iSSD* m_Ssd;
};