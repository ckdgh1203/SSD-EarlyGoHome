#pragma once
#include <string>
#include <vector>
#include <deque>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <direct.h>
#include "iFile.h"
#include "iSSD.h"

using namespace std;

class FileSingleton : public iFile
{
public:
	static FileSingleton& getInstance()
	{
		static FileSingleton instance{};
		return instance;
	}

	void setFilePath(string prefixPath)
	{
		DATA_DIR = getDirectoryPath(prefixPath) + "/" + DATA_DIR;
		NAND_FILE = DATA_DIR + "/" + NAND_FILE;
		RESULT_FILE = DATA_DIR + "/" + RESULT_FILE;
		BUFFER_FILE = DATA_DIR + "/" + BUFFER_FILE;

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

	void initTxtFiles()
	{
		vector<string> buf;
		for (int i = START_LBA; i < MAX_LBA_RANGE; i++)
		{
			buf.push_back(DEFAULT_DATA);
		}
		writeToNANDTxt(buf);
		writeToResultTxt(DEFAULT_DATA);
	}

	vector<string> readFromNANDTxt() override
	{
		ifstream file(NAND_FILE);
		vector<string> ret;

		if (!file.is_open())
		{
			for (int i = START_LBA; i < MAX_LBA_RANGE; i++)
			{
				ret.push_back(DEFAULT_DATA);
			}
			return ret;
		}

		getLBAData(file, ret);
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
		string ret = DEFAULT_DATA;
		string temp;

		if (!file.is_open())
		{
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

	void readFromBuffertxt(deque<CommandPacket>& cmdBuf, int& cmdCnt)
	{
		ifstream file(BUFFER_FILE);
		string line;

		cmdBuf.clear();

		if (!file.is_open())
		{
			cmdCnt = 0;
			return;
		}

		while (getline(file, line))
		{
			vector<string> words = splitBySpace(line);
			cmdBuf.push_back(CommandPacket{ words[0]/*command*/, stoi(words[1]) /*startLba*/, stoi(words[2])/*endLba*/, words[3]/*data*/ });
		}

		cmdCnt = cmdBuf.size();

		file.close();

		return;
	}

	void writeToBufferTxt(string data)
	{
		ofstream file(BUFFER_FILE, std::ios_base::trunc);
		if (file.is_open())
		{
			file << data;
			file.close();
		}
	}

	string getResultPath()
	{
		if (!resultFileExist)
			return "";
		return RESULT_FILE;
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

	vector<string> splitBySpace(const string& str)
	{
		vector<string> words;
		string word;
		for (char ch : str)
		{
			if (ch == ' ')
			{
				if (!word.empty())
				{
					words.push_back(word);
					word.clear();
				}
			}
			else
			{
				word += ch;
			}
		}
		if (!word.empty())
		{
			words.push_back(word);
		}
		return words;
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
		if (!fileExists(BUFFER_FILE))
		{
			ofstream file(BUFFER_FILE);
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

	string DATA_DIR = "/Data";
	string NAND_FILE = "nand.txt";
	string RESULT_FILE = "result.txt";
	string BUFFER_FILE = "buffer.txt";

	bool resultFileExist = false;
};