#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "iFile.h"

using namespace std;

const string NAND_FILE = "nand.txt";
const string RESULT_FILE = "result.txt";
const string DEFAULT_DATA = "0x00000000";

class SSDFile : public iFile
{
public:
	string readFromNANDTxt(int lba) override
	{
		ifstream file(NAND_FILE);
		string ret = DEFAULT_DATA;

		if (!file.is_open())
		{
			cout << "read file open fail" << endl;
			return ret;
		}

		getLBAData(lba, file, ret);
		file.close();

		return ret;
	}

	void writeToNANDTxt(vector<string> buf) override
	{
		ofstream file(NAND_FILE);
		if (!file.is_open())
		{
			cout << "write file open fail" << endl;
			return;
		}

		for (const string& updateLine : buf)
		{
			file << updateLine << endl;
		};

		file.close();
	}

	string readFromResultTxt(int lba) override
	{
		ifstream file(RESULT_FILE);
		string ret = DEFAULT_DATA;

		if (!file.is_open())
		{
			cout << "read file open fail" << endl;
			return ret;
		}

		getLBAData(lba, file, ret);
		file.close();

		return ret;
	}

	void writeToResultTxt(int lba, string data) override
	{}

private:
	void getLBAData(int lba, ifstream& file, string& ret)
	{
		int targetLine = 0;
		string buf;
		while(getline(file, buf))
		{
			if (targetLine == lba)
			{
				ret = buf;
			}
			targetLine++;
		}
	}
};