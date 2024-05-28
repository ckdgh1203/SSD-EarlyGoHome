#include <string>
#include <vector>
#include <deque>
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
			fastWrite(cmdPacket);
		}
		
		if (cmdPacket.command == "E")
		{
			fastErase(cmdPacket);
		}

		saveCmdBuffer();

		return true;
	}

	deque<CommandPacket> getCommandFromCommandBuffer()
	{
		deque<CommandPacket> ret = cmdBuf;
		cmdBuf.clear();
		cmdCnt = 0;
		return ret;
	}

private:
	deque<CommandPacket> cmdBuf;
	int cmdCnt = 0;

	bool fastRead(CommandPacket cmdPacket)
	{
		for (int i = (int)cmdBuf.size() - 1; i >= 0; i--)
		{
			if ((cmdBuf[i].startLba <= cmdPacket.startLba) && (cmdPacket.startLba <= cmdBuf[i].endLba))
			{
				FileSingleton::getInstance().writeToResultTxt(cmdBuf[i].data);
				return true;
			}
		}

		return false;
	}

	void ignore(CommandPacket cmdPacket)
	{
		deque<CommandPacket> tempBuf;

		for (int i = 0 ; i < cmdBuf.size() ; i++)
		{
			if (!((cmdPacket.startLba <= cmdBuf[i].startLba) && (cmdBuf[i].endLba <= cmdPacket.endLba)))
			{
				tempBuf.push_back(cmdBuf[i]);
			}
		}

		cmdBuf.clear();
		cmdBuf = tempBuf;
		cmdCnt = cmdBuf.size();
	}

	void fastWrite(CommandPacket cmdPacket)
	{
		ignore(cmdPacket);
		cmdBuf.push_back(cmdPacket);
		cmdCnt++;
	}

	void fastErase(CommandPacket cmdPacket)
	{
		ignore(cmdPacket);
		cmdBuf.push_back(cmdPacket);
		cmdCnt++;
	}

	void saveCmdBuffer()
	{
		string data = "";
		for (int i = 0; i < cmdBuf.size(); i++)
		{
			data = data + cmdBuf[i].command + " " + to_string(cmdBuf[i].startLba) + " " + to_string(cmdBuf[i].endLba) + " " + cmdBuf[i].data + "\n";
		}
		FileSingleton::getInstance().writeToBufferTxt(data);
	}
};

