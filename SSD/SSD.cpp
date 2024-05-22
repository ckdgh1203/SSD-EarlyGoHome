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
		m_file->writeToResultTxt(lba, m_file->readFromNANDTxt(lba));
	}
	void write(int lba, string data) override
	{
		m_file->readFromNANDTxt(lba);
		m_file->writeToNANDTxt(lba, data);
	}

private:
	iFile* m_file;
};