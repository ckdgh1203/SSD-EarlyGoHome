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
		for (int currentLBA = 0; currentLBA < 100; currentLBA++)
		{
			m_file->writeToNANDTxt(currentLBA, buf[currentLBA]);
		}
	}

	vector<string> dataReadFromNand()
	{
		vector<string> buf;
		string targetData;
		for (int currentLBA = 0; currentLBA < 100; currentLBA++)
		{
			targetData = m_file->readFromNANDTxt(currentLBA);
			buf.push_back(targetData);
		}
		return buf;
	}

	bool isInvalidData(const string data)
	{
		if (data.length() != 10)
		{
			//cout << "Data invalid length! " << endl;
			return true;;
		}

		if (data[0] != '0' || data[1] != 'x')
		{
			//cout << "Data is not Hex format! " << endl;
			return true;  
		}

		for (int i = 2; i < 10; i++)
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
		if (lba < 0 || lba >= 100)
		{
			//cout << "LBA invalid range! " << endl;
			return true;
		}
		return false;
	}

private:
	iFile* m_file;
};