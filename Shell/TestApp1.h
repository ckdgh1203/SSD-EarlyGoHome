#pragma once

#include "ScriptHandler.h"

class TestApp1 : public ScriptHandler
{
public:
	TestApp1(ostringstream& stringStream, SsdHelper& ssdHelper)
		: ScriptHandler(stringStream, ssdHelper) {}

	bool doScript() override;
};