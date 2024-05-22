#include "../SSD/iSSD.h"

class Shell
{
public:
	Shell(void) {}
	Shell(iSSD* ssd) : m_ssd(ssd) {}
	string read(unsigned int lba)
	{
		return "Out of Lba";
	}
private:
	iSSD* m_ssd{};
};