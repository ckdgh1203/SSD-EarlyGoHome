#pragma once
#include <string>

using namespace std;

class iSSD
{
public:
	virtual void read(int lba) = 0;
	virtual void write(int lba, string data) = 0;
};