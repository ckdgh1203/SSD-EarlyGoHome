#pragma once

#include <iostream>

#include "ZipAlgo.h"
#include "Logger.h"

using namespace std;

class SimpleZip : public ZipAlgo
{
public:
    bool doZip(std::string& oldFileName) const override
    {
		std::string newFileName = oldFileName;
		size_t dotIndex = newFileName.find_last_of('.');
		if (dotIndex != std::string::npos)
		{
			newFileName.replace(dotIndex, newFileName.size() - dotIndex, ".zip");
		}
		if (changeFileName(oldFileName, newFileName))
		{
			return true;
		}
		return false;
    }
private:
	// Simple Zip Algorithm.
	bool changeFileName(std::string from, std::string to) const
	{
		std::wstring oldWstr(from.begin(), from.end());
		std::wstring newWstr(to.begin(), to.end());

		return MoveFile(oldWstr.c_str(), newWstr.c_str());
	}
};

