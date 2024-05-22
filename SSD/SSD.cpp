#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include "iSSD.h"
#include "iFile.h"

using namespace std;

class SSD : public iSSD
{
public:
	SSD(iFile* iFile) : m_file(iFile)
	{
	}

	void read(int lba) override
	{

	}
	void write(int lba, string data) override
	{

	}

private:
	iFile* m_file;
};