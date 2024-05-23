#include <iostream>
#include <string>
#include "SSD.cpp"
#include "File.cpp"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 2 || argc > 4)
		return 0;

	SSDFile file;
	SSD ssd{};
	string cmd = argv[1];
	int lba = lba = stoi(argv[2]);

	if (cmd == "R")
	{
		ReadCommand rCmd{&file, lba };
		ssd.setCommand(&rCmd);
		ssd.executeCommand();
	}
	
	if (cmd == "W")
	{
		string data = argv[3];
		WriteCommand wCmd{ &file, lba, data };
		ssd.setCommand(&wCmd);
		ssd.executeCommand();
	}

	return 0;
}