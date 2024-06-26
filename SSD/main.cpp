#include <iostream>
#include <string>
#include "SSD.cpp"
using namespace std;

bool isInvalidLbaRange(int lba);
bool isHexFormat(char ch);
bool isInvalidData(const string data);
bool isInvalidEraseSize(int size);
bool argValidityCheckAndMakeCmdPack(CommandPacket& cmdPacket, int argc, char* argv[]);

int main(int argc, char* argv[])
{
	CommandPacket cmdPacket = {};
	if (argValidityCheckAndMakeCmdPack(cmdPacket, argc, argv) == RETURN_FAIL)
	{
		return RETURN_FAIL;
	}

	SSD ssd{};
	CommandFactory& commandFactory = CommandFactory::getInstance();
	FileSingleton& fileSingleton = FileSingleton::getInstance();
	fileSingleton.setFilePath(__FILE__);
	if (cmdPacket.command == GETPATH_COMMAND)
	{
		cout << fileSingleton.getResultPath() << endl;
		return RETURN_FAIL;
	}

	if (cmdPacket.command == FLUSH_COMMAND)
	{
		ssd.setCommand(commandFactory.createCommand(ssd.getBufferedCommand()));
		ssd.executeCommand();
	}
	else
	{
		if (ssd.bufferingCommand(cmdPacket) == RETURN_FAIL)
		{
			if (cmdPacket.command == READ_COMMAND)
			{
				ssd.setCommand(commandFactory.createCommand(cmdPacket.startLba));
				ssd.executeCommand();
			}
			else
			{
				ssd.setCommand(commandFactory.createCommand(ssd.getBufferedCommand()));
				ssd.executeCommand();
				if (ssd.bufferingCommand(cmdPacket) == RETURN_FAIL)	
				{
					cout << "[ERROR] Command Buffering Fail after Flush!" << endl;
					return RETURN_FAIL;
				}
			}
		}
	}

	return RETURN_SUCCESS;
}



bool isInvalidLbaRange(int lba)
{
	return ((START_LBA > lba) || (lba >= MAX_LBA_RANGE));
}

bool isHexFormat(char ch)
{
	return ('0' <= ch && ch <= '9') || ('A' <= ch && ch <= 'F');
}

bool isNumberFormat(char ch)
{
	return ('0' <= ch && ch <= '9');
}

bool isInvalidData(const string data)
{
	if (data.length() != MAX_DATA_LENGTH)
	{
		return true;
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


bool argValidityCheckAndMakeCmdPack(CommandPacket& cmdPacket, int argc, char* argv[])
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
		string tmp = argv[3];
		for (int i = 0; i < tmp.size(); i++)
		{
			if (isNumberFormat(tmp[i]) == RETURN_FAIL)
			{
				cout << "[ERROR] [Not Number argument with Erase Command!]" << endl;
				return RETURN_FAIL;
			}
		}
		int size = stoi(tmp);
		cmdPacket.endLba = cmdPacket.startLba + size - 1;
		cmdPacket.data = DEFAULT_DATA;
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
	else if (cmdPacket.command == GETPATH_COMMAND)
	{
		if (argc != 2)
		{
			cout << "[ERROR] [GetPath Command needs 1 arg!]" << endl;
			return RETURN_FAIL;
		}
	}
	else
	{
		cout << "[ERROR] [Invalid SSD Command!]" << endl;
		return RETURN_FAIL;
	}
	return RETURN_SUCCESS;
}