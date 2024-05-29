#pragma once

#include <string>
#include <windows.h>

using namespace std;

class ZipAlgo
{
public:
	virtual ~ZipAlgo() = default;
	virtual bool doZip(std::string& data) const = 0;	
};