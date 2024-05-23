#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <exception>
#include <iostream>
#include "iSSD.h"
#include "iFile.h"

using namespace std;

const string NAND_FILE_NAME = "../Data/nand.txt";
const string RESULT_FILE_NAME = "../Data/result.txt";

class SSD : public iSSD
{
public:
	SSD(iFile* iFile) : m_file(iFile)
	{
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
		m_file->readFromNANDTxt(lba);
		m_file->writeToNANDTxt(lba, data);
	}

private:
	iFile* m_file;
};