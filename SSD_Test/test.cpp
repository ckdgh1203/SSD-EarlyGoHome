#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include "../SSD/iFile.h"
#include "../SSD/SSD.cpp"

using namespace std;
using namespace testing;

class MockFile : public iFile
{
public:
	MOCK_METHOD(void, readFromNANDTxt, (int), (override));
	MOCK_METHOD(void, writeToNANDTxt, (int, string), (override));
	MOCK_METHOD(void, readFromResultTxt, (int), (override));
	MOCK_METHOD(void, writeToResultTxt, (int, string), (override));
};

TEST(SSD_Test, LBA0_Read_Data_0x0000_0000_Success)
{
	MockFile mFile;
	SSD ssd(&mFile);
}

TEST(SSD_Test, LBA100_Read_Fail)
{

}

TEST(SSD_Test, LBA0_Write_Data_0x0000_0000_Success)
{

}

TEST(SSD_Test, LBA100_Write_Fail)
{

}

TEST(SSD_Test, LBA0_Write_Data_0x0000_0000_0000_Fail)
{

}
