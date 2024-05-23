#include <string>
#include <vector>
#include <iostream>
#include "iSSD.h"
#include "iFile.h"
using namespace std;

class Command
{
public:
	virtual void executeCommand() = 0;
};

class WriteCommand : public Command
{
public:
	WriteCommand(int lba, const string& data)
		: lba(lba), data(data)
	{}
	// Command을(를) 통해 상속됨
	void executeCommand() override
	{
		//Write 함수 여기로 이동시키기
	}

private:
	int lba;
	string data;
};

class ReadCommand : public Command
{
public:
	ReadCommand(int lba)
		: lba(lba)
	{}
	// Command을(를) 통해 상속됨
	void executeCommand() override
	{
		//Read 함수를 여기로 이동시키기
	}

private:
	int lba;
};