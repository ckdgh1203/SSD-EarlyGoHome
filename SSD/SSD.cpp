#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include "iSSD.h"

using namespace std;

class SSD : public iSSD
{
public:
	void read(int lba) override
	{

	}
	void write(int lba, string data) override
	{

	}
};