#pragma once
#include <string>

using namespace std;

class iSSD
{
public:
	virtual void read(int lba) = 0;
	virtual void write(int lba, string data) = 0;
};

typedef struct _CommandPacket
{
	string command;
	int startLba;
	int endLba;
	string data;
}CommandPacket;