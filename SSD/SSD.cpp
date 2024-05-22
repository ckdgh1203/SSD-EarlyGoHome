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

	vector<string> read(int lba) override
	{
		// 0~99 외의 값 예외 처리
		if (0 > lba || lba >= 100)
			throw exception("LBA(Logical Block Address)는 0에서 99까지의 수 이어야 합니다.");
		
		// nand.txt 파일 읽기
		string filename = "../Data/nand.txt";
		ifstream inputFile(filename);

		if(!inputFile.is_open())
			throw exception("파일을 정상적으로 열 수 없습니다.");

		string line;
		return 
		while (getline(inputFile, line))
		{
		}
		
		inputFile.close();

		// result.txt 파일에 저장
	}
	void write(int lba, string data) override
	{

	}

private:
	iFile* m_file;
};