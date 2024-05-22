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
	MOCK_METHOD(string, readFromNANDTxt, (int), (override));
	MOCK_METHOD(void, writeToNANDTxt, (int, string), (override));
	MOCK_METHOD(string, readFromResultTxt, (int), (override));
	MOCK_METHOD(void, writeToResultTxt, (int, string), (override));
};

TEST(SSD_Test, LBA0_Read_Data_Success)
{
	MockFile mFile;
	EXPECT_CALL(mFile, readFromNANDTxt(0))
		.Times(1);
	EXPECT_CALL(mFile, writeToResultTxt(0, "0x00000000"))
		.Times(1);

	SSD ssd(&mFile);
	ssd.read(0);
}

TEST(SSD_Test, LBA100_Read_Fail)
{
	MockFile mFile;
	EXPECT_CALL(mFile, readFromNANDTxt(0))
		.Times(0);
	EXPECT_CALL(mFile, writeToResultTxt(0, "0x12345678"))
		.Times(0);

	SSD ssd(&mFile);
	ssd.read(100);
}

TEST(SSD_Test, LBA0_Write_Data_0x1234_5678_Success)
{
	MockFile mFile;
	EXPECT_CALL(mFile, readFromNANDTxt(0))
		.Times(1);
	EXPECT_CALL(mFile, writeToNANDTxt(0, "0x12345678"))
		.Times(1);

	SSD ssd(&mFile);
	ssd.write(0, "0x12345678");
}

TEST(SSD_Test, LBA100_Write_Fail)
{
	MockFile mFile;
	EXPECT_CALL(mFile, readFromNANDTxt(0))
		.Times(0);
	EXPECT_CALL(mFile, writeToNANDTxt(0, "0x12345678"))
		.Times(0);

	SSD ssd(&mFile);
	ssd.write(0, "0x12345678");
}

TEST(SSD_Test, LBA0_Write_Data_0x0000_0000_0000_Fail)
{
	MockFile mFile;
	EXPECT_CALL(mFile, readFromNANDTxt(0))
		.Times(0);
	EXPECT_CALL(mFile, writeToNANDTxt(0, "0x000000000000"))
		.Times(0);

	SSD ssd(&mFile);
	ssd.write(0, "0x000000000000");
}
