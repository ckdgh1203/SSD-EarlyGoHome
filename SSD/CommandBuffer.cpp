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
		else if (cmdPacket.command == "E")
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
			if (cmdBuf[i].startLba <= cmdPacket.startLba && cmdPacket.startLba <= cmdBuf[i].endLba)
			{
				FileSingleton::getInstance().writeToResultTxt(cmdBuf[i].data);
				return true;
			}
		}

		return false;
	}

	void fastWrite(CommandPacket cmdPacket)
	{
		cmdBuf.push_back(cmdPacket);
		cmdCnt++;
	}

	int inputSmallOne(int a, int b)
	{
		return (a < b) ? a : b;
	}

	int inputBigOne(int a, int b)
	{
		return (a > b) ? a : b;
	}

	CommandPacket mergeCmdPacket(CommandPacket cmdPacket)
	{
		CommandPacket ret;
		ret.command = cmdPacket.command;
		ret.data = cmdPacket.data;
		ret.startLba = inputSmallOne(cmdBuf[cmdCnt - 1].startLba, cmdPacket.startLba);
		ret.endLba = inputBigOne(cmdBuf[cmdCnt - 1].endLba, cmdPacket.endLba);

		return ret;
	}

	bool isContinuedLbaRangeCmd(CommandPacket cmdPacket)
	{
		// 연속적이지 않을 경우
		if (!((cmdBuf[cmdCnt - 1].endLba + 1 >= cmdPacket.startLba) && (cmdBuf[cmdCnt - 1].startLba - 1 <= cmdPacket.endLba)))
			return false;

		int s = inputSmallOne(cmdBuf[cmdCnt - 1].startLba, cmdPacket.startLba);
		int e = inputBigOne(cmdBuf[cmdCnt - 1].endLba, cmdPacket.endLba);

		// 연속적이더라도 사이즈가 10보다 커질 경우
		if (e - s + 1 > 10)
			return false;
		
		return true;
	}

	void mergePreviousCommand(CommandPacket cmdPacket)
	{
		deque<CommandPacket> temp;
		for (int i = 0; i < cmdCnt - 1; i++)
			temp.push_back(cmdBuf[i]);

		if (cmdBuf[cmdCnt - 1].command == "E" && isContinuedLbaRangeCmd(cmdPacket))
			// merge 가능하면 merge
			temp.push_back(mergeCmdPacket(cmdPacket));
		else
		{	// merge 불가능하면 버퍼에 추가
			temp.push_back(cmdBuf[cmdCnt - 1]);
			temp.push_back(cmdPacket);
			cmdCnt++;
		}

		cmdBuf = temp;
	}

	void fastErase(CommandPacket cmdPacket)
	{
		mergePreviousCommand(cmdPacket);
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

