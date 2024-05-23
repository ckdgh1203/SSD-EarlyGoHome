#include <string>
#include <vector>
#include <iostream>
#include "iSSD.h"
#include "iFile.h"
using namespace std;

const string NAND_FILE_NAME = "../Data/nand.txt";
const string RESULT_FILE_NAME = "../Data/result.txt";

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
		cout << "WriteCommand execute() " << endl;
		//Write 함수 여기로 이동시키기
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
		for (int currentLBA = START_LBA; currentLBA < MAX_LBA_RANGE; currentLBA++)
		{
			m_file->writeToNANDTxt(currentLBA, buf[currentLBA]);
		}
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

	bool isInvalidData(const string data)
	{
		if (data.length() != MAX_DATA_LENGTH)
		{
			//cout << "Data invalid length! " << endl;
			return true;;
		}

		if (data[0] != '0' || data[1] != 'x')
		{
			//cout << "Data is not Hex format! " << endl;
			return true;
		}

		for (int i = 2; i < MAX_DATA_LENGTH; i++)
		{
			if (isHexFormat(data[i])) continue;
			//cout << "Data Hex invalid char! " << endl;
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
		cout << "ReadCommand execute() " << endl;
		//Read 함수를 여기로 이동시키기
		if (isInvalidLbaRange(lba))
			return;

		vector<string> nandTxt;
		for (int i = 0; i < 100; i++)
		{
			nandTxt.push_back(m_file->readFromNANDTxt(i));
		}

		m_file->writeToResultTxt(0, nandTxt[lba]);
	}

private:
	iFile* m_file;
	int lba;

};