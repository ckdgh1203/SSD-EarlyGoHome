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
	SSD ssd(&file);
	string cmd = argv[1];
	int lba = lba = stoi(argv[2]);

	if (cmd == "R")
	{
		ssd.read(lba);
	}
	
	if (cmd == "W")
	{
		string data = argv[3];
		ssd.write(lba, data);
	}

	return 0;
}