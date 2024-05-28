#pragma once

#include "ScriptHandler.cpp"

using namespace std;

class TestApp4 : public ScriptHandler
{
public:
	TestApp4(ostringstream& stringStream, SsdHelper& ssdHelper)
		: ScriptHandler(stringStream, ssdHelper)
	{

	}

	bool doScript() override
	{
		doFullRead();

		istringstream iString(m_stringStream.str());
		vector<string> outputVector;
		string outputString;

		while (getline(iString, outputString))
		{
			outputVector.push_back(outputString);

			if (outputVector.size() <= 1) continue;

			int lastElem = outputVector.size() - 1;
			if (outputVector[0] != outputVector[lastElem])
				return false;
		}

		return true;
	}
};