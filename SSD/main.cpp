#include <iostream>
#include <string>
#include "SSD.cpp"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 2 || argc > 4)
		return 0;

	CommandFactory& commandFactory = CommandFactory::getInstance();
	FileSingleton& fileSingleton = FileSingleton::getInstance();
	fileSingleton.setFilePath("Data/");

	SSD ssd{};
	CommandPacket cmdPacket = {};
	cmdPacket.command = argv[1];
	cmdPacket.startLba = stoi(argv[2]);
	//string cmd = argv[1];
	//int lba = lba = stoi(argv[2]);

	//argument 정리해서 CommandPacket으로 정리

	if (cmdPacket.command == "R")
	{
		// cmd buffer에 read 있는지 확인
		if (ssd.executeFastRead(cmdPacket))
			return 0;
		//있다면 여기서 리턴

		//없다면 아래
		ssd.setCommand(commandFactory.createCommand(cmdPacket.startLba));
	}
	
	if (cmdPacket.command == "W")
	{
		//string data = argv[3];
		cmdPacket.endLba = cmdPacket.startLba;
		cmdPacket.data = argv[3];
		if (ssd.isNeedFlush())
		{
			ssd.flush();
		}
		ssd.bufferingCommand(cmdPacket);
		//ssd.setCommand(commandFactory.createCommand(cmdPacket.startLba, cmdPacket.data));
	}
	if (cmdPacket.command == "E")
	{
		//int size = stoi(argv[3]);
		cmdPacket.endLba = cmdPacket.startLba + stoi(argv[3]) - 1;
		cmdPacket.data = "0x00000000";
		if (ssd.isNeedFlush())
		{
			ssd.flush();
		}
		ssd.bufferingCommand(cmdPacket);
		//ssd.setCommand(commandFactory.createCommand(cmdPacket.startLba, cmdPacket.size));
	}
	ssd.executeCommand();

	return 0;
}