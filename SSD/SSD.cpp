#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include "iSSD.h"
#include "iFile.h"
#include <iostream>
using namespace std;

class SSD : public iSSD
{
public:
	SSD(iFile* iFile) : m_file(iFile)
	{
	}

	void read(int lba) override
	{
		m_file->writeToResultTxt(lba, m_file->readFromNANDTxt(lba));
	}
	void write(int lba, string data) override
	{
		cout << "Write LBA : " << lba << endl;
		// W 명령어 사용시 : nand.txt 파일 내용 전체 읽어온 후, 특정부분을변경하고새로Write를수행한다.
		//1. LBA validity check
		if (isInvalidLbaRange(lba))
		{
			return;
		}

		//2. data validity check
		if (isInvalidData(data))
		{
			return;
		}
		
		cout << "validity pass!!" << endl;

		//3. readFromNANDTxt 전체 읽어오기
		vector<string> buf;
		string targetData;
		for (int currentLBA = 0; currentLBA < 100; currentLBA++)
		{
			targetData = m_file->readFromNANDTxt(currentLBA);
			buf.push_back(targetData);
		}

		//4. 읽은 부분에서 target lba data 수정하기
		buf[lba] = data;

		//5. writeToNANDTxt 전체 내용 다시 쓰기 
		for (int currentLBA = 0; currentLBA < 100; currentLBA++)
		{
			m_file->writeToNANDTxt(currentLBA, buf[currentLBA]);
		}
	}

	bool isInvalidData(const string data)
	{
		if (data.length() != 10)
		{
			cout << "Data invalid length! " << endl;
			return true;;
		}

		if (data[0] != '0' || data[1] != 'x')
		{
			cout << "Data is not Hex format! " << endl;
			return true;  
		}

		for (int i = 2; i < 10; i++)
		{
			if ((data[i] >= '0' && data[i] <= '9') || (data[i] >= 'A' && data[i] <= 'F')) continue;
			cout << "Data Hex invalid char! " << endl;
			return true;
		}
		return false;
	}

	bool isInvalidLbaRange(int lba)
	{
		if (lba < 0 || lba >= 100)
		{
			cout << "LBA invalid range! " << endl;
			return true;
		}
		return false;
	}

private:
	iFile* m_file;
};