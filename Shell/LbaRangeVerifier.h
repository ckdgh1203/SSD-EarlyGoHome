#pragma once

#include <string>

class LbaRangeVerifier
{
public:
	bool isInvalidLba(const std::string& lbaString)
	{
		for (auto c : lbaString)
		{
			if (false == isdigit(c)) return true;
		}
		return isLbaOutOfRange(stoi(lbaString));
	}

	bool isLbaOutOfRange(const int lba)
	{
		return lba < 0 || lba > 99;
	}
};