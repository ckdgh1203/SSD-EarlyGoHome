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
	void insertCommandToCommandBuffer(CommandPacket cmdPacket)
	{

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

