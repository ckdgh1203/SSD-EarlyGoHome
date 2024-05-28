#include <string>
#include <vector>
#include <iostream>
#include "iSSD.h"
#include "iFile.h"
#include "FileSingleton.cpp"

using namespace std;

class CommandBuffer
{
public:
	const int MAX_BUFFER_SIZE = 10;

	bool insertCommandToCommandBuffer(CommandPacket cmdPacket)
	{
		FileSingleton::getInstance().readFromBuffertxt(cmdBuf, cmdCnt);

		if (cmdPacket.command == "R")
		{
			return fastRead(cmdPacket);
		}

		if (cmdCnt == MAX_BUFFER_SIZE)
		{
			return false;
		}

		if (cmdPacket.command == "W")
		{
			fastWrite();
		}
		else if (cmdPacket.command == "E")
		{
			fastErase();
		}
		return true;
	}

	vector<CommandPacket> getCommandFromCommandBuffer()
	{
		return cmdBuf;
	}

private:
	vector<CommandPacket> cmdBuf;
	int cmdCnt = 0;

	bool fastRead(CommandPacket cmdPacket)
	{
		for (int i = (int)cmdBuf.size() - 1; i >= 0; i--)
		{
			if (cmdBuf[i].startLba <= cmdPacket.startLba && cmdPacket.startLba <= cmdBuf[i].endLba)
			{
				FileSingleton::getInstance().writeToResultTxt(cmdBuf[i].data);
				return true;
			}
		}

		return false;
	}

	void fastWrite()
	{

	}

	void fastErase()
	{

	}

	void saveCmdBuffer()
	{
		string data = to_string(cmdCnt) + "\n";
		for (int i = 0; i < cmdBuf.size(); i++)
		{
			data = data + cmdBuf[i].command + " " + to_string(cmdBuf[i].startLba) + " " + to_string(cmdBuf[i].endLba) + " " + cmdBuf[i].data + "\n";
		}
		FileSingleton::getInstance().writeToBufferTxt(data);
	}
};

