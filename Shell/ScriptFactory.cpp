#pragma once

#include "ScriptHandler.cpp"
#include "TestApp1.cpp"
#include "TestApp2.cpp"

#include <iostream>
#include <sstream>

using namespace std;

class ScriptFactory
{
public:
	ScriptHandler* create(const string& scriptStr, SsdHelper& ssdHelper)
	{
		ScriptEnum scriptEnum = CovertStrToScriptEnum(scriptStr);
		switch (scriptEnum)
		{
		case TESTAPP1:
			return new TestApp1(m_stringStream, ssdHelper);
		case TESTAPP2:
			return new TestApp2(m_stringStream, ssdHelper);
		default:
			return nullptr;
		}
	}
private:
	typedef enum
	{
		TESTAPP1,
		TESTAPP2,
		MAX_SCRIPT
	} ScriptEnum;

	ScriptEnum CovertStrToScriptEnum(const string& scriptStr)
	{
		if (scriptStr == "testapp1") return TESTAPP1;
		if (scriptStr == "testapp2") return TESTAPP2;

		return MAX_SCRIPT;
	}

	ostringstream m_stringStream{};
};