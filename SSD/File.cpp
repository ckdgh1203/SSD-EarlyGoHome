#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <direct.h>
#include "iFile.h"

using namespace std;

class SSDFile : public iFile
{
public:
	SSDFile(string prefixPath)
	{
		DATA_DIR = getDirectoryPath(prefixPath) + "/" + DATA_DIR;
		NAND_FILE = DATA_DIR + "/" + NAND_FILE;
		RESULT_FILE = DATA_DIR + "/" + RESULT_FILE;

		if (!directoryExists(DATA_DIR))
		{
			if (_mkdir(DATA_DIR.c_str()) == 0)
			{
				createOutputFiles();
			}
		}
		else
		{
			createOutputFiles();
		}
	}

	void createOutputFiles()
	{
		if (!fileExists(NAND_FILE))
		{
			ofstream file(NAND_FILE);
			if (file)
			{
				file.close();
			}
		}
		if (!fileExists(RESULT_FILE))
		{
			ofstream file(RESULT_FILE);
			if (file)
			{
				resultFileExist = true;
				file.close();
			}
		}
		else
		{
			resultFileExist = true;
		}
	}

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

	string getResultPath()
	{
		if (!resultFileExist)
			return "";
		return RESULT_FILE;
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

	string getDirectoryPath(string filePath)
	{
		size_t lastSlashPos = filePath.find_last_of('/\\');
		string dirPath = filePath;
		if (lastSlashPos != std::string::npos)
		{
			dirPath = filePath.substr(0, lastSlashPos);
		}
		return dirPath;
	}

	bool fileExists(const std::string& fileName)
	{
		struct stat buffer;

		return (stat(fileName.c_str(), &buffer) == 0);
	}

	bool directoryExists(const std::string& dirPath)
	{
		struct stat info;

		if (stat(dirPath.c_str(), &info) != 0)
		{
			return false;
		}
		else if (info.st_mode & S_IFDIR)
		{
			return true;
		}

		return false;
	}

	string DATA_DIR = "/Data";
	string NAND_FILE = "nand.txt";
	string RESULT_FILE = "result.txt";
	bool resultFileExist = false;
	const string DEFAULT_DATA = "0x00000000";
};