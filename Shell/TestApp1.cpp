#include "TestApp1.h"

void TestApp1::doScript()
{
	doFullWrite("0xDEADC0DE");
	duFullRead();

	bool isCompareSuccess = readCompare("0xDEADC0DE", 0, 100);

	if (false == isCompareSuccess)
	{
		m_stringStream << "[WARNING] testapp1 : written data is different with read data!!!" << endl;
		cout << m_stringStream.str();
		return;
	}

	m_stringStream << "testapp1 : Done test, written data is same with read data :)" << endl;
	cout << m_stringStream.str();
}
