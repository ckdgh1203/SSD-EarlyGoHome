#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "iFile.h"

using namespace std;
const string DEFAULT_DATA = "0x00000000";

class FileSingleton : public iFile
{
public:
	const string NAND_FILE = "nand.txt";
	const string RESULT_FILE = "result.txt";

	static FileSingleton& getInstance()
	{
		static FileSingleton instance{};
		return instance;
	}

	void setFilePath(string file)
	{
		filePath = file;
	}

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

	vector<string> readFromNANDTxt() override
	{
		ifstream file(filePath + NAND_FILE);
		vector<string> ret;
		for (int i = 0; i < 100; i++)
		{
			ret.push_back(DEFAULT_DATA);
		}

		if (!file.is_open())
		{
			cout << "read file open fail" << endl;
			return ret;
		}

		getLBAData(file, ret);
		file.close();

		return ret;
	}

	void writeToNANDTxt(vector<string> buf) override
	{
		ofstream file(filePath + NAND_FILE);
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
		ifstream file(filePath + RESULT_FILE);
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
		ofstream file(filePath + RESULT_FILE);
		if (!file.is_open())
		{
			cout << "write file open fail" << endl;
			return;
		}

		file << data << endl;

		file.close();
	}


private:
	FileSingleton() {}
	FileSingleton& operator=(const FileSingleton& other) = delete;
	FileSingleton(const FileSingleton& other) = delete;

	void getLBAData(ifstream& file, vector<string>& ret)
	{
		int targetLine = 0;
		string buf;
		while (getline(file, buf))
		{
			ret[targetLine++] = buf;
		}
	}
	string filePath;
};