#pragma once

#include "ScriptHandler.cpp"
#include "testapp1.cpp"
#include "testapp2.cpp"

#include <iostream>
#include <sstream>

using namespace std;

class ScriptFactory
{
public:
	ScriptFactory* create(const string& scriptStr)
	{
		ScriptEnum scriptEnum = CovertStrToScriptEnum(scriptStr);
		switch (scriptEnum)
		{
		case TESTAPP1:
			return new TestApp1();
		case TESTAPP2:
			return new TestApp2();
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

	ScriptEnum CovertStrToScriptEnum(const string& commandStr)
	{
		if (commandStr == "testapp1") return TESTAPP1;
		if (commandStr == "testapp2") return TESTAPP2;

		return MAX_SCRIPT;
	}
};