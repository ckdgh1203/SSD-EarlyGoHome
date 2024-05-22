#include "../SSD/iSSD.h"

#include <iostream>
#include <stdexcept>

using namespace std;

class iExit
{
public:
	virtual void doExit() = 0;
private:
};

class Exit : public iExit
{
public:
	void doExit() override
	{
		exit(0);
	}
private:
};

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

	Shell(void) 
	{
		_exit = new Exit();
	}

	Shell(iSSD* ssd) : m_ssd(ssd)
	{
		_exit = new Exit();
	}

	void help()
	{
		helpMessasge();
	}

	void helpMessasge()
	{
		cout << "This is Help Message" << endl;
	}

	void exit()
	{ 
		_exit->doExit();
	}

	void setExit(iExit *newExit)
	{
		_exit = newExit;
	}

	string read(unsigned int lba)
	{
		if (verifyLba(lba)) return "Out of Lba";
		m_ssd->read(static_cast<int>(lba));
		// read result from result.txt
		return "0x00000000";
	}

	void write(unsigned int lba, const string& data)
	{
		if (verifyLba(lba)) return;
		if (verifyDataFormat(data)) return;
		m_ssd->write(static_cast<int>(lba), data);
	}

	void fullwrite(const string inputData)
	{
		checkInputDataForPrefix(inputData);
		checkInputDataForInvalid(inputData);

		for (int iter = 0; iter < 100; iter++)
		{
			m_ssd->write(iter, inputData);
		}
	}

	void fullread()
	{
		for (int iter = 0; iter < 100; iter++)
		{
			m_ssd->read(iter);
		}
	}

private:
	iSSD* m_ssd{};
	iExit* _exit;

	bool verifyLba(unsigned int lba)
	{
		return 99 < lba;
	}

	bool verifyDataFormat(const std::string& data)
	{
		return data.size() != 10;
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
};