#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <exception>
#include <iostream>
#include "iSSD.h"
#include "iFile.h"
#include <iostream>
#include "Command.cpp"
using namespace std;
const int MAX_LBA_RANGE = 100;
const int MAX_DATA_LENGTH = 10;
const int START_LBA = 0;

const string NAND_FILE_NAME = "../Data/nand.txt";
const string RESULT_FILE_NAME = "../Data/result.txt";

class SSD : public iSSD
{
public:
	SSD(iFile* m_file, Command* command)
		: m_file(m_file), command(command)
	{}

	void executeCommand()
	{
		command->executeCommand();
	}
	
	void setCommand(Command* newCommand)
	{
		command = newCommand;
	}

	void read(int lba) override
	{
		if (isNotValidLbaRange(lba))
			return;
		// throw exception("LBA(Logical Block Address)는 0에서 99까지의 수 이어야 합니다.");
		
		vector<string> nandTxt;
		for (int i = 0; i < 100; i++)
		{
			nandTxt.push_back(m_file->readFromNANDTxt(i));
		}
		// bool isReadFromNANDFlag = m_file->readFromNANDTxt(nandTxt);

		/* readFromNANDTxt 구현부
		ifstream inputFile(NAND_FILE_NAME);

		if (!inputFile.is_open())
			return;
		// throw exception("파일을 정상적으로 열 수 없습니다.");

		int lineNum = 0;
		string line;
		string lbaLine;

		while (getline(inputFile, line))
		{
			if (lineNum == lba)
				lbaLine = line;
			lineNum++;
		}
		
		inputFile.close();
		*/

		m_file->writeToResultTxt(0, nandTxt[lba]);

		/* writeToResultTxt 구현부
		// result.txt 파일에 저장
		ofstream outputFile(RESULT_FILE_NAME);

		if (!outputFile)
			throw exception("파일을 정상적으로 열 수 없습니다.");

		outputFile << ret << std::endl;
		
		outputFile.close();
		*/
	}

	bool isNotValidLbaRange(int lba)
	{
		return 0 > lba || lba >= 100;
	}

	void write(int lba, string data) override
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

	bool isInvalidLbaRange(int lba)
	{
		if (lba < START_LBA || lba >= MAX_LBA_RANGE)
		{
			//cout << "LBA invalid range! " << endl;
			return true;
		}
		return false;
	}

private:
	iFile* m_file;
	Command* command;

};