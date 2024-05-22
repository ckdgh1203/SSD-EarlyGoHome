#include <string>
#include <vector>
#include <filesystem>
#include <fstream>

using namespace std;

class iSSD
{
public:
	virtual void read(int lba) = 0;
	virtual void write(int lba, string data) = 0;
};

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