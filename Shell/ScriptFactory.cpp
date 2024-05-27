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
	ScriptHandler* create(const string& scriptStr, CommandFactory& commandFactory, ostream& outputStream)
	{
		ScriptEnum scriptEnum = CovertStrToScriptEnum(scriptStr);
		switch (scriptEnum)
		{
		case TESTAPP1:
			return new TestApp1(commandFactory, outputStream);
		case TESTAPP2:
			return new TestApp2(commandFactory, outputStream);
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