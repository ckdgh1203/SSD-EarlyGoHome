#pragma once

#include "ScriptHandler.h"

class TestApp1 : public ScriptHandler
{
public:
	TestApp1(ostringstream& stringStream, SsdHelper& ssdHelper)
		: ScriptHandler(stringStream, ssdHelper) {}

	bool doScript() override;
	string usage(void) override { return "testapp1 or FullWriteAndFullReadAndCompare\n"; };
};