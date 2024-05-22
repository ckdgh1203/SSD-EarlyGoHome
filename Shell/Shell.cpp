#include "../SSD/iSSD.h"
#include "SsdExcutable.h"

#include <iostream>
#include <sstream>

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

	Shell(ISsdExecutable* executable) : m_ssdExcutable(executable)
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

	void run(istream& inputStream)
	{
		string userInput;
		while (true)
		{
			cout << "shell> ";
			getline(inputStream, userInput);
			cout << userInput << endl;
			if (userInput == "exit")
			{
				exit();
				return;
			}

			if (userInput.find("read") == 0)
			{
				read(3);
			}
		}
	}

	string read(unsigned int lba)
	{
		if (verifyLba(lba)) return "Out of Lba";
		m_ssdExcutable->execute("R 3\n");
		// read result from result.txt
		return "0x00000000";
	}

	void write(unsigned int lba, const string& data)
	{
		if (verifyLba(lba)) return;
		if (verifyDataFormat(data)) return;
		string arguments = "W " + to_string(lba) + " " + data + "\n";
		m_ssdExcutable->execute(arguments);
	}
	
private:
	iSSD* m_ssd{};
	iExit* _exit;
	ISsdExecutable* m_ssdExcutable{};

	bool verifyLba(unsigned int lba)
	{
		return 99 < lba;
	}

	bool verifyDataFormat(const std::string& data)
	{
		return data.size() != 10;
	}
};