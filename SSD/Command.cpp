#include <string>
#include <vector>
#include <iostream>
#include "iSSD.h"
#include "iFile.h"
using namespace std;

class Command
{
public:
	virtual void executeCommand(int lba) = 0;
	virtual void executeCommand(int lba, string data) = 0;
};

