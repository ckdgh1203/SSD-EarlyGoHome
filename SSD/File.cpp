#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include "iFile.h"

using namespace std; 

class SSDFile : public iFile
{
public:
	void readFromNANDTxt(int lba) override
	{
	}

	void writeToNANDTxt(int lba, string data) override
	{
	}

	void readFromResultTxt(int lba) override
	{
	}

	void writeToResultTxt(int lba, string data) override
	{
	}
};