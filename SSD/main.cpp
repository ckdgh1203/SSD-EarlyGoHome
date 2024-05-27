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
	string cmd = argv[1];
	int lba = lba = stoi(argv[2]);

	if (cmd == "R")
	{
		ssd.setCommand(commandFactory.createCommand(lba));
	}
	
	if (cmd == "W")
	{
		string data = argv[3];
		ssd.setCommand(commandFactory.createCommand(lba, data));
	}
	if (cmd == "E")
	{
		int size = stoi(argv[3]);
		ssd.setCommand(commandFactory.createCommand(lba, size));
	}
	ssd.executeCommand();

	return 0;
}