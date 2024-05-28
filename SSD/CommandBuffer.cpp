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
	bool insertCommandToCommandBuffer(CommandPacket cmdPacket)
	{
		FileSingleton::getInstance().readFromBuffertxt(cmdBuf, cmdCnt);

		if (cmdPacket.command == READ_COMMAND)
		{
			return fastRead(cmdPacket);
		}

		if (cmdCnt == MAX_BUFFER_SIZE)
		{
			return false;
		}

		if (cmdPacket.command == WRITE_COMMAND)
		{
			fastWrite(cmdPacket);
		}
		
		if (cmdPacket.command == ERASE_COMMAND)
		{
			fastErase(cmdPacket);
		}

		saveCmdBuffer();

		return true;
	}

	deque<CommandPacket> getCommandFromCommandBuffer()
	{
		FileSingleton::getInstance().readFromBuffertxt(cmdBuf, cmdCnt);
		deque<CommandPacket> ret = cmdBuf;
		cmdBuf.clear();
		cmdCnt = 0;
		saveCmdBuffer();
		return ret;
	}

private:
	deque<CommandPacket> cmdBuf;
	int cmdCnt = 0;
	const int MAX_BUFFER_SIZE = 10;

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

	void ignorePreviousCommand(CommandPacket cmdPacket)
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

	void makeContinousWritePacket(CommandPacket& continuosWrite)
	{
		for (int i = 0; i < cmdCnt - 1; i++)
		{
			if ((cmdBuf[i].command == WRITE_COMMAND) && (cmdBuf[i].startLba + 1 == continuosWrite.startLba))
			{
				continuosWrite.startLba = cmdBuf[i].startLba;
				makeContinousWritePacket(continuosWrite);
			}

			if ((cmdBuf[i].command == WRITE_COMMAND) && (cmdBuf[i].startLba - 1 == continuosWrite.endLba))
			{
				continuosWrite.endLba = cmdBuf[i].startLba;
				makeContinousWritePacket(continuosWrite);
			}
		}
	}

	void resizeEraseSize(CommandPacket& continuosWrite)
	{
		for (int i = 0; i < cmdCnt; i++)
		{
			if (cmdBuf[i].command == ERASE_COMMAND)
			{
				// 앞 resize
				if((cmdBuf[i].startLba <= continuosWrite.endLba) && (cmdBuf[i].startLba >= continuosWrite.startLba))
				{
					cmdBuf[i].startLba = continuosWrite.endLba + 1;
				}

				// 뒤 resize cmdBuf[0].endLba 
				if ((cmdBuf[i].endLba >= continuosWrite.startLba) && (cmdBuf[i].endLba <= continuosWrite.endLba))
				{
					cmdBuf[i].endLba = continuosWrite.startLba - 1;
				}
			}
		}
	}

	void narrowRangeOfErase()
	{
		if (cmdCnt < 2)
		{
			return;
		}

		CommandPacket continuosWrite = cmdBuf[cmdCnt - 1];
		makeContinousWritePacket(continuosWrite);
		resizeEraseSize(continuosWrite);

		deque<CommandPacket> temp;
		for (int i = 0; i < cmdCnt; i++)
		{
			if (cmdBuf[i].startLba <= cmdBuf[i].endLba)
			{
				temp.push_back(cmdBuf[i]);
			}
		}

		cmdBuf.clear();
		cmdBuf = temp;
		cmdCnt = cmdBuf.size();
	}

	void fastWrite(CommandPacket cmdPacket)
	{
		ignorePreviousCommand(cmdPacket);
		cmdBuf.push_back(cmdPacket);
		cmdCnt++;
		narrowRangeOfErase();
	}

	CommandPacket mergeCmdPacket(CommandPacket cmdPacket)
	{
		CommandPacket ret;
		ret.command = cmdPacket.command;
		ret.data = cmdPacket.data;
		ret.startLba = min(cmdBuf[cmdCnt - 1].startLba, cmdPacket.startLba);
		ret.endLba = max(cmdBuf[cmdCnt - 1].endLba, cmdPacket.endLba);

		return ret;
	}

	bool isContinuedLbaRangeCmd(CommandPacket cmdPacket)
	{
		// 연속적이지 않을 경우
		if (!((cmdBuf[cmdCnt - 1].endLba + 1 >= cmdPacket.startLba) && (cmdBuf[cmdCnt - 1].startLba - 1 <= cmdPacket.endLba)))
		{
			return false;
		}

		int s = min(cmdBuf[cmdCnt - 1].startLba, cmdPacket.startLba);
		int e = max(cmdBuf[cmdCnt - 1].endLba, cmdPacket.endLba);

		// 연속적이더라도 사이즈가 10보다 커질 경우
		if (e - s + 1 > MAX_ERASE_SIZE)
		{
			return false;
		}
		
		return true;
	}

	void mergePreviousCommand(CommandPacket cmdPacket)
	{
		deque<CommandPacket> temp;
		for (int i = 0; i < cmdCnt - 1; i++)
		{
			temp.push_back(cmdBuf[i]);
		}

		if (cmdBuf[cmdCnt - 1].command == ERASE_COMMAND && isContinuedLbaRangeCmd(cmdPacket))
		{
			// merge 가능하면 merge
			temp.push_back(mergeCmdPacket(cmdPacket));
		}
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
		ignorePreviousCommand(cmdPacket);
		cmdBuf.push_back(cmdPacket);
		cmdCnt++;
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

