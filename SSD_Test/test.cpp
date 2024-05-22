#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include "../SSD/iSSD.h"

using namespace std;
using namespace testing;

class MockSSD : public iSSD
{
public:
	MOCK_METHOD(void, read, (int), (override));
	MOCK_METHOD(void, write, (int, string), (override));
};