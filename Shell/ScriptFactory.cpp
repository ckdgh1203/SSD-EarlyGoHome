#pragma once

#include "ScriptHandler.cpp"
#include "TestApp1.cpp"
#include "TestApp2.cpp"
#include "FullWriteAndReadCompare.cpp"
#include "FullRead10AndCompare.cpp"
#include "Write10AndCompare.cpp"
#include "LoopWriteAndReadCompare.cpp"
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
		case FULLWRITE_AND_READCOMPARE:
			return new FullWriteAndReadCompare(commandFactory, outputStream);
		case FULLREAD10_AND_COMPARE:
			return new FullRead10AndCompare(commandFactory, outputStream);
		case WRITE10_AND_COMPARE:
			return new Write10AndCompare(commandFactory, outputStream);
		case LOOP_WRITE_AND_READCOMPARE:
			return new LoopWriteAndReadCompare(commandFactory, outputStream);
		default:
			return nullptr;
		}
	}
private:
	typedef enum
	{
		TESTAPP1,
		TESTAPP2,
		FULLWRITE_AND_READCOMPARE,
		FULLREAD10_AND_COMPARE,
		WRITE10_AND_COMPARE,
		LOOP_WRITE_AND_READCOMPARE,
		MAX_SCRIPT
	} ScriptEnum;

	ScriptEnum CovertStrToScriptEnum(const string& scriptStr)
	{
		if (scriptStr == "testapp1") return TESTAPP1;
		if (scriptStr == "testapp2") return TESTAPP2;
		if (scriptStr == "FullWriteAndReadCompare") return FULLWRITE_AND_READCOMPARE;
		if (scriptStr == "FullRead10AndCompare") return FULLREAD10_AND_COMPARE;
		if (scriptStr == "Write10AndCompare") return WRITE10_AND_COMPARE;
		if (scriptStr == "LoopWriteAndReadCompare") return LOOP_WRITE_AND_READCOMPARE;

		return MAX_SCRIPT;
	}
};