#include "../SSD/iSSD.h"

#include <cstdlib>

class Shell
{
public:
	Shell(void) {}
	Shell(iSSD* ssd) : m_ssd(ssd) {}

	string read(unsigned int lba)
	{
		if (verifyLba(lba)) return "Out of Lba";
		m_ssd->read(static_cast<int>(lba));
		// read result from result.txt
		return "0x00000000";
	}

	void write(unsigned int lba, const string& data)
	{
		if (verifyLba(lba)) return;
		if (verifyDataFormat(data)) return;
		m_ssd->write(static_cast<int>(lba), data);
	}
private:
	iSSD* m_ssd{};

	bool verifyLba(unsigned int lba)
	{
		return 99 < lba;
	}

	bool verifyDataFormat(const std::string& data)
	{
		return data.size() != 10;
	}
};