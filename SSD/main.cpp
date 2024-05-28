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
		if (argc != 4)
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
		if (argc != 3)
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
		if (argc != 4)
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
		if (argc != 2)
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
	CommandPacket cmdPacket = {};
	ArgValidityCheckAndMakeCmdPack(cmdPacket, argc, argv);

	CommandFactory& commandFactory = CommandFactory::getInstance();
	FileSingleton& fileSingleton = FileSingleton::getInstance();
	fileSingleton.setFilePath("Data/");

	SSD ssd{};
	cmdPacket.command = argv[1];
	
	if (cmdPacket.command == "F")
	{
		ssd.setCommand(commandFactory.createCommand(ssd.getBufferedCommand()));
		ssd.executeCommand();
	}
	else
	{
		if (ssd.bufferingCommand(cmdPacket) == RETURN_FAIL)
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
				if (ssd.bufferingCommand(cmdPacket) == RETURN_FAIL)	
				{
					//그럴리가 없는 상태
					return 0;
				}
			}
		}
	}

	return 0;
}
