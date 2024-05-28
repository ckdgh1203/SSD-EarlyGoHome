#include <string>
#include <vector>
#include <iostream>
#include "iSSD.h"
#include "iFile.h"
#include "FileSingleton.cpp"
using namespace std;

class Command
{
public:
	virtual void executeCommand() = 0;

protected:
	string ERASE_DATA = "0x00000000";

};

class WriteCommand : public Command
{
public:
	WriteCommand(int lba, const string& data)
		: lba(lba), data(data)
	{}

	void executeCommand() override
	{
		vector<string> buf = dataReadFromNand();
		dataWriteToTargetLba(buf, lba, data);
		dataWriteToNand(buf);
	}
	void dataWriteToTargetLba(std::vector<std::string>& buf, int lba, std::string& data)
	{
		buf[lba] = data;
	}

	void dataWriteToNand(std::vector<std::string>& buf)
	{
		FileSingleton::getInstance().writeToNANDTxt(buf);
	}

	vector<string> dataReadFromNand()
	{
		vector<string> buf;
		buf = FileSingleton::getInstance().readFromNANDTxt();
		return buf;
	}

private:
	int lba;
	string data;
};

class ReadCommand : public Command
{
public:
	ReadCommand(int lba)
		: lba(lba)
	{}

	void executeCommand() override
	{
		vector<string> nandTxt;
		nandTxt = FileSingleton::getInstance().readFromNANDTxt();
		FileSingleton::getInstance().writeToResultTxt(nandTxt[lba]);
	}

private:
	int lba;
};

class EraseCommand : public Command
{
public:
	EraseCommand(int lba, int size)
		: lba(lba), size(size)
	{}

	void executeCommand() override
	{
		vector<string> buf = dataReadFromNand();
		dataEraseToTargetLba(buf);
		dataWriteToNand(buf);
	}

	void dataEraseToTargetLba(std::vector<std::string>& buf)
	{
		for (int i = lba; i < lba + size; i++)
		{
			dataWriteToTargetLba(buf, i, ERASE_DATA);
		}
	}

	void dataWriteToTargetLba(std::vector<std::string>& buf, int lba, std::string& data)
	{
		buf[lba] = data;
	}

	void dataWriteToNand(std::vector<std::string>& buf)
	{
		FileSingleton::getInstance().writeToNANDTxt(buf);
	}

	vector<string> dataReadFromNand()
	{
		vector<string> buf;
		buf = FileSingleton::getInstance().readFromNANDTxt();
		return buf;
	}

private:
	int lba;
	int size;
};


class FlushCommand : public Command
{
public:
	FlushCommand(const deque<Command*>& commandBuffer)
		: commandBuffer(commandBuffer)
	{}

	void executeCommand() override
	{
		for (deque<Command*>::size_type i = 0; i < commandBuffer.size(); i++)
		{
			commandBuffer[i]->executeCommand();
		}
	}

private:
	deque<Command*> commandBuffer;
};