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
	{}
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
	
	deque<Command*> getBufferedCommand()
	{
		deque<Command*> bufferedCommand = {};
		deque<CommandPacket> cmdPack = commandBuffer.getCommandFromCommandBuffer();
		for (deque<CommandPacket>::size_type i = 0; i < cmdPack.size(); i++)
		{
			if (cmdPack[i].command == "W")
			{
				bufferedCommand.push_back(CommandFactory::getInstance().createCommand(cmdPack[i].startLba, cmdPack[i].data));
			}
			else if (cmdPack[i].command == "E")
			{
				bufferedCommand.push_back(CommandFactory::getInstance().createCommand(cmdPack[i].startLba, cmdPack[i].endLba - cmdPack[i].startLba + 1));
			}
		}
		return bufferedCommand;
	}

private:
	Command* command;
	CommandBuffer commandBuffer;
};
