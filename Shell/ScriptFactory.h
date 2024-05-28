#pragma once

#include "ScriptHandler.h"

#include <iostream>
#include <sstream>

using namespace std;

class ScriptFactory
{
public:
	ScriptHandler* create(const string& scriptStr, SsdHelper& ssdHelper);
private:
	typedef enum
	{
		TESTAPP1,
		TESTAPP2,
		MAX_SCRIPT
	} ScriptEnum;

	ScriptEnum CovertStrToScriptEnum(const string& scriptStr);

	ostringstream m_stringStream{};
};