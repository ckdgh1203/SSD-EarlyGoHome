#include "ScriptFactory.h"
#include "TestApp1.h"
#include "TestApp2.h"

ScriptHandler* ScriptFactory::create(const string& scriptStr, SsdHelper& ssdHelper)
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

ScriptFactory::ScriptEnum ScriptFactory::CovertStrToScriptEnum(const string& scriptStr)
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
