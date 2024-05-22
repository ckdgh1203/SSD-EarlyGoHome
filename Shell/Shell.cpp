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

	void checkInputDataForPrefix(const std::string& inputData)
	{
		if (inputData[0] != '0' || inputData[1] != 'x')
		{
			throw NotIncludedPrefix();
		}
	}

	void checkInputDataForInvalid(const std::string& inputData)
	{
		for (int index = 2; index < inputData.length(); index++)
		{
			if (('A' <= inputData[index] && inputData[index] <= 'Z') || ('0' <= inputData[index] && inputData[index] <= '9'))
			{
				continue;
			}

			throw NotAllowedInputData();
		}
	}

	void fullwrite(const string inputData)
	{
		checkInputDataForPrefix(inputData);
		checkInputDataForInvalid(inputData);

		for (int iter = 0; iter < 100; iter++)
		{
			m_Ssd->write(iter, inputData);
		}
	}

	void fullread()
	{
		for (int iter = 0; iter < 100; iter++)
		{
			m_Ssd->read(iter);
		}
	}
private:
	iSSD* m_Ssd;
};