#pragma once
#include<string>

class LbaRangeVerifier
{
public:
	bool isLbaOutOfRange(const int lba)
	{
		return lba < 0 || lba > 99;
	}
};