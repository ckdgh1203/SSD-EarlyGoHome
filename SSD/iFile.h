#pragma once
#include <vector>
#include <string>

using namespace std;

class iFile
{
public:
	virtual string readFromNANDTxt(int lba) = 0;
	virtual void writeToNANDTxt(vector<string> buf) = 0;

	virtual string readFromResultTxt(int lba) = 0;
	virtual void writeToResultTxt(int lba, string data) = 0;
};