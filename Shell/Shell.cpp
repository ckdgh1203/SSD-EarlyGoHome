#include "../SSD/iSSD.h"

#include <iostream>

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
		if (false == IsInputDataWithPrefix(inputData))	return;
		if (false == IsInputDataWithValidRange(inputData)) return;

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

	bool IsInputDataWithPrefix(const std::string& inputData)
	{
		if (inputData[0] != '0' || inputData[1] != 'x')
		{
			cout << "[WARNING] Prefix '0x' was not included in input data !!!" << endl;
			return false;
		}

		return true;
	}

	bool IsInputDataWithValidRange(const std::string& inputData)
	{
		for (int index = 2; index < inputData.length(); index++)
		{
			if (('A' <= inputData[index] && inputData[index] <= 'F') || ('0' <= inputData[index] && inputData[index] <= '9'))
			{
				continue;
			}

			cout << "[WARNING] Input data has invalid characters !!!" << endl;
			return false;
		}

		return true;
	}
};