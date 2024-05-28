#include <string>
#include <vector>
#include <iostream>
#include "iSSD.h"
#include "iFile.h"

class CommandBuffer
{
public:
	int getBufferedCommandCount()
	{
		return 0;
	}
	bool insertCommandToCommandBuffer(CommandPacket cmdPacket)
	{
		return 0;
	}
	bool executeFastReadInCommandBuffer(CommandPacket cmdPacket)
	{
		return 0;
	}
	vector<CommandPacket> getCommandFromCommandBuffer()
	{
		vector<CommandPacket> tmp = {};
		return tmp;
	}
};

