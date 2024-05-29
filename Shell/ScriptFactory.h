#pragma once

#include "ScriptHandler.h"
#include "TestApp1.h"
#include "TestApp2.h"
#include "TestApp3.h"
#include "TestApp4.h"
#include "TestApp5.h"
#include "TestApp6.h"
#include <iostream>
#include <sstream>

using namespace std;

class ScriptFactory
{
public:
	ScriptHandler* create(const string& scriptStr, SsdHelper& ssdHelper);
	const std::vector<string> getCommandList(void);
private:
	typedef enum
	{
		TESTAPP1,
		TESTAPP2,
		TESTAPP3,
		TESTAPP4,
		TESTAPP5,
		TESTAPP6,
		MAX_SCRIPT
	} ScriptEnum;

	ScriptEnum CovertStrToScriptEnum(const string& scriptStr);

	ostringstream m_stringStream{};
};