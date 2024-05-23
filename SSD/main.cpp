#include <iostream>
#include <string>
#include "SSD.cpp"
#include "File.cpp"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 2 || argc > 4)
		return 0;

	CommandFactory& commandFactory = CommandFactory::getInstance();
	SSDFile file;
	SSD ssd{};
	string cmd = argv[1];
	int lba = lba = stoi(argv[2]);

	if (cmd == "R")
	{
		ssd.setCommand(commandFactory.createCommand(&file, lba));
		ssd.executeCommand();
	}
	
	if (cmd == "W")
	{
		string data = argv[3];
		ssd.setCommand(commandFactory.createCommand(&file, lba, data));
		ssd.executeCommand();
	}

	return 0;
}