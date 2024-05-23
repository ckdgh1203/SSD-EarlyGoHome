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
	WriteCommand(iFile* m_file, int lba, const string& data)
		: m_file(m_file), lba(lba), data(data)
	{}
	// Command을(를) 통해 상속됨
	void executeCommand() override
	{
		cout << "WriteCommadn execute() " << endl;
		//Write 함수 여기로 이동시키기
		//if (isInvalidLbaRange(lba) || isInvalidData(data))
		//{
		//	return;
		//}
		//vector<string> buf = dataReadFromNand();
		//dataWriteToTargetLba(buf, lba, data);
		//dataWriteToNand(buf);
	}

private:
	iFile* m_file;
	int lba;
	string data;

};

class ReadCommand : public Command
{
public:
	ReadCommand(iFile* m_file, int lba)
		: m_file(m_file), lba(lba)
	{}
	// Command을(를) 통해 상속됨
	void executeCommand() override
	{
		cout << "ReadCommadn execute() " << endl;
		//Read 함수를 여기로 이동시키기
	}

private:
	iFile* m_file;
	int lba;

};