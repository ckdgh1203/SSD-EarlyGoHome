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
using namespace std;

class SSD
{
public:
	SSD() 
		: command(nullptr)
	{
	}
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

private:
	Command* command;

};