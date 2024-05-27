#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "iFile.h"

using namespace std;

const string NAND_FILE = "Data/nand.txt";
const string RESULT_FILE = "Data/result.txt";
const string DEFAULT_DATA = "0x00000000";
const string NAND_FILE_FOR_TEST = "../Data/nand.txt";
const string RESULT_FILE_FOR_TEST = "../Data/result.txt";

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

	string readFromResultTxt() override
	{
		ifstream file(RESULT_FILE);
		string ret;
		string temp;

		if (!file.is_open())
		{
			cout << "read file open fail" << endl;
			return ret;
		}

		getline(file, temp);
		ret = temp;

		file.close();

		return ret;
	}

	void writeToResultTxt(string data) override
	{
		ofstream file(RESULT_FILE);
		if (!file.is_open())
		{
			cout << "write file open fail" << endl;
			return;
		}

		file << data << endl;

		file.close();
	}

private:
	void getLBAData(int lba, ifstream& file, string& ret)
	{
		int targetLine = 0;
		string buf;
		while (getline(file, buf))
		{
			if (targetLine == lba)
			{
				ret = buf;
			}
			targetLine++;
		}
	}
};

class SSDFileTest : public iFile
{
public:
	void initTxtFiles()
	{
		vector<string> buf;
		for (int i = 0; i < 100; i++)
		{
			buf.push_back(DEFAULT_DATA);
		}
		writeToNANDTxt(buf);
		writeToResultTxt(DEFAULT_DATA);
	}

	string readFromNANDTxt(int lba) override
	{
		ifstream file(NAND_FILE_FOR_TEST);
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
		ofstream file(NAND_FILE_FOR_TEST);
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

	string readFromResultTxt() override
	{
		ifstream file(RESULT_FILE_FOR_TEST);
		string ret;
		string temp;

		if (!file.is_open())
		{
			cout << "read file open fail" << endl;
			return ret;
		}

		getline(file, temp);
		ret = temp;

		file.close();

		return ret;
	}

	void writeToResultTxt(string data) override
	{
		ofstream file(RESULT_FILE_FOR_TEST);
		if (!file.is_open())
		{
			cout << "write file open fail" << endl;
			return;
		}

		file << data << endl;

		file.close();
	}

private:
	void getLBAData(int lba, ifstream& file, string& ret)
	{
		int targetLine = 0;
		string buf;
		while (getline(file, buf))
		{
			if (targetLine == lba)
			{
				ret = buf;
			}
			targetLine++;
		}
	}
};