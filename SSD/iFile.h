#pragma once
#include <string>

using namespace std;

class iFile
{
public:
	virtual void readFromNANDTxt(int lba) = 0;
	virtual void writeToNANDTxt(int lba, string data) = 0;

	virtual void readFromResultTxt(int lba) = 0;
	virtual void writeToResultTxt(int lba, string data) = 0;
};