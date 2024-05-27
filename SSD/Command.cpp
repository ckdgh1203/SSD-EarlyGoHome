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
	bool isInvalidLbaRange(int lba)
	{
		return ((START_LBA > lba) || (lba >= MAX_LBA_RANGE));
	}
	const int MAX_LBA_RANGE = 100;
	const int MAX_DATA_LENGTH = 10;
	const int START_LBA = 0;
	const int MAX_ERASE_SIZE = 10;
	const int MIN_ERASE_SIZE = 0;
	string ERASE_DATA = "0x00000000";

};

class WriteCommand : public Command
{
public:
	WriteCommand(iFile* m_file, int lba, const string& data)
		: m_file(m_file), lba(lba), data(data)
	{}
	// Command을(를) 통해 상속됨
	void executeCommand() override
	{
		if (isInvalidLbaRange(lba) || isInvalidData(data))
		{
			return;
		}
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
		m_file->writeToNANDTxt(buf);
	}

	vector<string> dataReadFromNand()
	{
		vector<string> buf;
		string targetData;
		//for (int currentLBA = START_LBA; currentLBA < MAX_LBA_RANGE; currentLBA++)
		//{
		//	targetData = m_file->readFromNANDTxt(currentLBA);

		//	buf.push_back(targetData);
		//}
		FileSingleton& fileSingleton = FileSingleton::getInstance();
		for (int currentLBA = START_LBA; currentLBA < MAX_LBA_RANGE; currentLBA++)
		{
			targetData = fileSingleton.readFromNANDTxt(currentLBA);

			buf.push_back(targetData);
		}
		return buf;
	}

	bool isInvalidData(const string data)
	{
		if (data.length() != MAX_DATA_LENGTH)
		{
			return true;;
		}

		if (data[0] != '0' || data[1] != 'x')
		{
			return true;
		}

		for (int i = 2; i < MAX_DATA_LENGTH; i++)
		{
			if (isHexFormat(data[i])) continue;
			return true;
		}
		return false;
	}

	bool isHexFormat(char ch)
	{
		return ('0' <= ch && ch <= '9') || ('A' <= ch && ch <= 'F');
	}

private:
	iFile* m_file;
	int lba;
	string data;
	//FileSingleton& fileSingleton;

};

class ReadCommand : public Command
{
public:
	ReadCommand(iFile* m_file, int lba)
		: m_file(m_file), lba(lba)
	{}
	// Command을(를) 통해 상속됨
	void executeCommand() override
	{
		if (isInvalidLbaRange(lba))
			return;

		vector<string> nandTxt;
		for (int i = 0; i < MAX_LBA_RANGE; i++)
		{
			nandTxt.push_back(m_file->readFromNANDTxt(i));
		}

		m_file->writeToResultTxt(nandTxt[lba]);
	}

private:
	iFile* m_file;
	int lba;

};

class EraseCommand : public Command
{
public:
	EraseCommand(iFile* m_file, int lba, int size)
		: m_file(m_file), lba(lba), size(size)
	{}
	// Command을(를) 통해 상속됨
	void executeCommand() override
	{
		if (isInvalidEraseSize() || isInvalidLbaRange(lba))
			return;

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

	bool isInvalidEraseSize()
	{
		return (size > MAX_ERASE_SIZE) || (size <= MIN_ERASE_SIZE);
	}

	void dataWriteToTargetLba(std::vector<std::string>& buf, int lba, std::string& data)
	{
		buf[lba] = data;
	}

	void dataWriteToNand(std::vector<std::string>& buf)
	{
		m_file->writeToNANDTxt(buf);
	}

	vector<string> dataReadFromNand()
	{
		vector<string> buf;
		string targetData;
		for (int currentLBA = START_LBA; currentLBA < MAX_LBA_RANGE; currentLBA++)
		{
			targetData = m_file->readFromNANDTxt(currentLBA);
			buf.push_back(targetData);
		}
		return buf;
	}

private:
	iFile* m_file;
	int lba;
	int size;
};