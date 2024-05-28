#include <iostream>
#include <string>
#include "SSD.cpp"
#include "File.cpp"
#include <windows.h>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc <= 1)
		return 0;

	string cmd = argv[1];

	if (cmd != "G" && (argc < 3 || argc > 4))
		return 0;

	CommandFactory& commandFactory = CommandFactory::getInstance();
	SSDFile file{ __FILE__ };
	SSD ssd{};
	if (cmd == "G")
	{
		cout << file.getResultPath() << endl;
		return 0;
	}

	int lba = stoi(argv[2]);

	if (cmd == "R")
	{
		ssd.setCommand(commandFactory.createCommand(&file, lba));
	}
	
	if (cmd == "W")
	{
		string data = argv[3];
		ssd.setCommand(commandFactory.createCommand(&file, lba, data));
	}

	ssd.executeCommand();

	return 0;
}