#include <iostream>
#include <string>
#include "SSD.cpp"

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

bool isInvalidLbaRange(int lba)
{
	return ((START_LBA > lba) || (lba >= MAX_LBA_RANGE));
}

bool isHexFormat(char ch)
{
	return ('0' <= ch && ch <= '9') || ('A' <= ch && ch <= 'F');
}

bool isInvalidData(const string data)
{
	if (data.length() != MAX_DATA_LENGTH)
	{
		return true;;
	}

	if (data[0] != '0' || data[1] != 'x')
	{
		return true;
	}

	for (int i = 2; i < MAX_DATA_LENGTH; i++)
	{
		if (isHexFormat(data[i])) continue;
		return true;
	}
	return false;
}

bool isInvalidEraseSize(int size)
{
	return (size > MAX_ERASE_SIZE) || (size <= MIN_ERASE_SIZE);
}

bool ArgValidityCheckAndMakeCmdPack(CommandPacket& cmdPacket, int argc, char* argv[])
{
	if (argc == 0)
	{
		cout << "[ERROR] [No Argument]" << endl;
		return RETURN_FAIL;
	}

	cmdPacket.command = argv[1];
	if (cmdPacket.command == WRITE_COMMAND)
	{
		if (argc != 3)
		{
			cout << "[ERROR] [Write command needs 3 arg!]" << endl;
			return RETURN_FAIL;
		}
		cmdPacket.startLba = stoi(argv[2]);
		cmdPacket.endLba = cmdPacket.startLba;
		cmdPacket.data = argv[3];

		if (isInvalidLbaRange(cmdPacket.startLba) || isInvalidData(cmdPacket.data))
		{
			cout << "[ERROR] [Invalid argument with Write Command!]" << endl;
			return RETURN_FAIL;
		}
	}
	else if (cmdPacket.command == READ_COMMAND)
	{
		if (argc != 2)
		{
			cout << "[ERROR] [Read command needs 2 arg!]" << endl;
			return RETURN_FAIL;
		}
		cmdPacket.startLba = stoi(argv[2]);

		if (isInvalidLbaRange(cmdPacket.startLba))
		{
			cout << "[ERROR] [Invalid argument with Read Command!]" << endl;
			return RETURN_FAIL;
		}

	}
	else if (cmdPacket.command == ERASE_COMMAND)
	{
		if (argc != 3)
		{
			cout << "[ERROR] [Erase command needs 3 arg!]" << endl;
			return RETURN_FAIL;
		}
		cmdPacket.startLba = stoi(argv[2]);
		int size = stoi(argv[3]);
		cmdPacket.endLba = cmdPacket.startLba + size - 1;
		cmdPacket.data = ERASE_DATA;
		if (isInvalidEraseSize(size) || isInvalidLbaRange(cmdPacket.startLba))
		{
			cout << "[ERROR] [Invalid argument with Erase Command!]" << endl;
			return RETURN_FAIL;
		}
	}
	else if (cmdPacket.command == FLUSH_COMMAND)
	{
		if (argc != 1)
		{
			cout << "[ERROR] [Flush Command needs 1 arg!]" << endl;
			return RETURN_FAIL;
		}
	}
	else
	{
		cout << "[ERROR] [Invalid SSD Command!]" << endl;
		return RETURN_FAIL;
	}
}

int main(int argc, char* argv[])
{
	if (argc < 3 || argc > 4)
		return 0;

	CommandFactory& commandFactory = CommandFactory::getInstance();
	FileSingleton& fileSingleton = FileSingleton::getInstance();
	fileSingleton.setFilePath("Data/");

	SSD ssd{};
	CommandPacket cmdPacket = {};
	cmdPacket.command = argv[1];
	
	//1. argument 정리해서 CommandPacket만들기 함수 호출

	//2. ssd.bufferingCommand()
	//2-1. R case. return false면 ReadCmd create
	//             return true면 그대로 CmdBuffer에서 FastRead 수행
	//2-2. W/E case. return false면 NeedFlush 상태임. Flush cmd 생성해서 수행하고 다시 bufferingCommand()호출
	//				 return true면 CommandBuffering 성공
	//* F case. 는 if문으로 따로 처리하고 F아닌경우 bufferingCommand()호출하자
	if (cmdPacket.command == "F")
	{
		ssd.setCommand(commandFactory.createCommand(ssd.getBufferedCommand()));
		ssd.executeCommand();
	}
	else
	{
		if (cmdPacket.command == "R")
		{
			cmdPacket.startLba = stoi(argv[2]);
		}
		else if (cmdPacket.command == "W")
		{
			cmdPacket.startLba = stoi(argv[2]);
			cmdPacket.endLba = cmdPacket.startLba;
			cmdPacket.data = argv[3];
		}
		else if (cmdPacket.command == "E")
		{
			cmdPacket.startLba = stoi(argv[2]);
			cmdPacket.endLba = cmdPacket.startLba + stoi(argv[3]) - 1;
			cmdPacket.data = "0x00000000";
		}

		if (ssd.bufferingCommand(cmdPacket) == 0)	// Fail return
		{
			if (cmdPacket.command == "R")
			{
				ssd.setCommand(commandFactory.createCommand(cmdPacket.startLba));
				ssd.executeCommand();
			}
			else
			{
				// W, E에서 Need Flush인 상태
				//Flush Cmd 생성 + execute
				ssd.setCommand(commandFactory.createCommand(ssd.getBufferedCommand()));
				ssd.executeCommand();
				if (ssd.bufferingCommand(cmdPacket) == 0)	// Fail return
				{
					//그럴리가 없는 상태
					return 0;
				}
			}
		}
	}

	return 0;
}
