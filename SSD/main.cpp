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
	//1. argument 정리해서 CommandPacket만들기 함수 호출

	//2. ssd.bufferingCommand()
	//2-1. R case. return false면 ReadCmd create
	//             return true면 그대로 CmdBuffer에서 FastRead 수행
	//2-2. W/E case. return false면 NeedFlush 상태임. Flush cmd 생성해서 수행하고 다시 bufferingCommand()호출
	//				 return true면 CommandBuffering 성공
	//* F case. 는 if문으로 따로 처리하고 F아닌경우 bufferingCommand()호출하자
	if (cmdPacket.command == "F")
	{

		//ssd.setCommand(commandFactory.createCommand(cmdPacket.startLba, cmdPacket.data));
	}
	else
	{
		if (cmdPacket.command == "R")
		{

		}
		else if (cmdPacket.command == "W")
		{
			cmdPacket.endLba = cmdPacket.startLba;
			cmdPacket.data = argv[3];
		}
		else if (cmdPacket.command == "E")
		{
			cmdPacket.endLba = cmdPacket.startLba + stoi(argv[3]) - 1;
			cmdPacket.data = "0x00000000";
		}

		if (ssd.bufferingCommand(cmdPacket) == 0)	// Fail return
		{
			if (cmdPacket.command == "R")
			{
				ssd.setCommand(commandFactory.createCommand(cmdPacket.startLba));
				ssd.executeCommand();
			}
			else
			{
				// W, E에서 Need Flush인 상태
				//Flush Cmd 생성 + execute
				//ssd.executeCommand();
				if (ssd.bufferingCommand(cmdPacket) == 0)	// Fail return
				{
					//그럴리가 없는 상태
					return 0;
				}
			}
		}
	}

	return 0;
}
