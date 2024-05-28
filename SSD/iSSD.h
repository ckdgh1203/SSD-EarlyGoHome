#pragma once
#include <string>

using namespace std;
const string WRITE_COMMAND = "W";
const string READ_COMMAND = "R";
const string ERASE_COMMAND = "E";
const string FLUSH_COMMAND = "F";
const string ERASE_DATA = "0x00000000";
const int RETURN_FAIL = 0;
const int RETURN_SUCCESS = 1;
const int MAX_LBA_RANGE = 100;
const int MAX_DATA_LENGTH = 10;
const int START_LBA = 0;
const int MAX_ERASE_SIZE = 10;
const int MIN_ERASE_SIZE = 0;

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