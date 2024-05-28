#pragma once

#include "ScriptHandler.cpp"
#include "TestApp1.cpp"
#include "TestApp2.cpp"
#include "TestApp3.cpp"
#include "TestApp4.cpp"
#include "TestApp5.cpp"
#include "TestApp6.cpp"
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
		case TESTAPP3:
			return new TestApp3(m_stringStream, ssdHelper);
		case TESTAPP4:
			return new TestApp4(m_stringStream, ssdHelper);
		case TESTAPP5:
			return new TestApp5(m_stringStream, ssdHelper);
		case TESTAPP6:
			return new TestApp6(m_stringStream, ssdHelper);
		default:
			return nullptr;
		}
	}
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

	ScriptEnum CovertStrToScriptEnum(const string& scriptStr)
	{
		if (scriptStr == "FullWriteAndFullReadAndCompare" || scriptStr == "testapp1")
			return TESTAPP1;
		if (scriptStr == "Write0to6Repeat30AndWrite0to6AndReadCompare" || scriptStr == "testapp2")
			return TESTAPP2;
		if (scriptStr == "FullWriteAndRead99AndCompare" || scriptStr == "testapp3")
			return TESTAPP3;
		if (scriptStr == "FullReadAndCompare" || scriptStr == "testapp4")
			return TESTAPP4;
		if (scriptStr == "Write0Repeat10AndReadCompare" || scriptStr == "testapp5")
			return TESTAPP5;
		if (scriptStr == "Write5to10AndWrite8to10AndReadCompare" || scriptStr == "testapp6")
			return TESTAPP6;

		return MAX_SCRIPT;
	}

	ostringstream m_stringStream{};
};