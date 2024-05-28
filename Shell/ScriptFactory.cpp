#include "ScriptFactory.h"
#include "TestApp1.cpp"
#include "TestApp2.cpp"

ScriptHandler* ScriptFactory::create(const string& scriptStr, SsdHelper& ssdHelper)
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

ScriptFactory::ScriptEnum ScriptFactory::CovertStrToScriptEnum(const string& scriptStr)
{
	if (scriptStr == "testapp1") return TESTAPP1;
	if (scriptStr == "testapp2") return TESTAPP2;

	return MAX_SCRIPT;
}
