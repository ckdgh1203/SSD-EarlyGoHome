#pragma once
#include <vector>
#include <string>

using namespace std;

class iFile
{
public:
	virtual vector<string> readFromNANDTxt() = 0;
	virtual void writeToNANDTxt(vector<string> buf) = 0;

	virtual string readFromResultTxt() = 0;
	virtual void writeToResultTxt(string data) = 0;
};