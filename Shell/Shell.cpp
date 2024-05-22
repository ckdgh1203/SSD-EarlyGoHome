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

	void run(void)
	{
		string cmdline;
		cin >> cmdline;
		if ("exit") exit();
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
};