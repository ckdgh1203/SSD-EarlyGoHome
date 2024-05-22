#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <exception>
#include <iostream>
#include "iSSD.h"
#include "iFile.h"

using namespace std;

class SSD : public iSSD
{
public:
	SSD(iFile* iFile) : m_file(iFile)
	{
	}

	void read(int lba) override
	{
		// 0~99 외의 값 예외 처리
		if (0 > lba || lba >= 100)
			return;
		// throw exception("LBA(Logical Block Address)는 0에서 99까지의 수 이어야 합니다.");
		
		// nand.txt 파일 읽기
		string filename = "../Data/nand.txt";
		ifstream inputFile(filename);

		if(!inputFile.is_open())
			throw exception("파일을 정상적으로 열 수 없습니다.");

		int i = 0;
		string line;
		string ret;
		while (getline(inputFile, line))
		{
			if (i == lba)
				ret = line;
			i++;
		}
		
		inputFile.close();

		// result.txt 파일에 저장
		ofstream outputFile("../Data/nand.txt");

		if (!outputFile)
			throw exception("파일을 정상적으로 열 수 없습니다.");

		outputFile << ret << std::endl;
		
		outputFile.close();

		// m_file->writeToResultTxt(lba, m_file->readFromNANDTxt(lba));
	}
	void write(int lba, string data) override
	{
		m_file->readFromNANDTxt(lba);
		m_file->writeToNANDTxt(lba, data);
	}

private:
	iFile* m_file;
};