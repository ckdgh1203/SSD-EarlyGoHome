#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <exception>
#include <iostream>
#include "iSSD.h"
#include "iFile.h"
#include <iostream>
#include "CommandFactory.cpp"
#include "CommandBuffer.cpp"
using namespace std;

class SSD
{
public:
	SSD() 
		: command(nullptr)
	{
	}
	SSD(Command* command)
		: command(command)
	{}

	void executeCommand()
	{
		command->executeCommand();
	}
	
	void setCommand(Command* newCommand)
	{
		command = newCommand;
	}


	bool bufferingCommand(CommandPacket cmdPacket)
	{
		return commandBuffer.insertCommandToCommandBuffer(cmdPacket);
	}

	void flush()
	{
		vector<CommandPacket> cmdPacket = {};
		int currentBufferedCommandCnt = commandBuffer.getBufferedCommandCount();
		for (int i = 0; i < currentBufferedCommandCnt; i++)
		{
			cmdPacket = commandBuffer.getCommandFromCommandBuffer();
			if (cmdPacket[i].command == "W")
			{
				setCommand(CommandFactory::getInstance().createCommand(cmdPacket[i].startLba, cmdPacket[i].data));
			}
			else if (cmdPacket[i].command == "U")
			{
				int size = cmdPacket[i].endLba - cmdPacket[i].startLba + 1;
				setCommand(CommandFactory::getInstance().createCommand(cmdPacket[i].startLba, size));
			}
			executeCommand();
		}
	}

private:
	Command* command;
	CommandBuffer commandBuffer;
};