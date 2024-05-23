#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include "../SSD/iFile.h"
#include "../SSD/SSD.cpp"
#include "../SSD/File.cpp"

using namespace std;
using namespace testing;

const int FILE_TEST_NUM = 100;

class MockFile : public iFile
{
public:
	MOCK_METHOD(string, readFromNANDTxt, (int), (override));
	MOCK_METHOD(void, writeToNANDTxt, (int, string), (override));
	MOCK_METHOD(string, readFromResultTxt, (int), (override));
	MOCK_METHOD(void, writeToResultTxt, (int, string), (override));
};

void ValidateFileTest(const string actualValue, const string expectedValue)
{
	EXPECT_EQ(actualValue, expectedValue);
}

class MockFileFixture : public testing::Test
{
public:
	void SetUp() override
	{
		ssd = new SSD(&mFile);
	}

	void TearDown() override
	{
		for (int i = 0; i < FILE_TEST_NUM; i++)
		{
			/*
			readnand -> 특정 줄 읽어서 비교
			writenand -> 넣은 줄 읽어서 비교?
			readresult -> 첫번째 줄 읽어서 비교
			writeresult -> 넣은 줄 읽어서 비교?
			*/
			ValidateFileTest(expected[i], actual[i]);
		}
	}

	NiceMock<MockFile> mFile;
	SSD* ssd;

protected:
	string expected[FILE_TEST_NUM];
	string actual[FILE_TEST_NUM];
};

TEST_F(MockFileFixture, Actual_Read_NAND_Success)
{
	SSDFile sFile;
	SSD* ssd = new SSD(&sFile);

	expected[1] = "0x00000000";
	actual[1] = "0x00000000";
}

TEST_F(MockFileFixture, Actual_Read_NAND_Fail)
{

}

TEST_F(MockFileFixture, Actual_Write_NAND_Success)
{

}

TEST_F(MockFileFixture, Actual_Write_NAND_Fail)
{

}

TEST_F(MockFileFixture, Actual_Read_RESULT_Success)
{

}

TEST_F(MockFileFixture, Actual_Read_RESULT_Fail)
{

}

TEST_F(MockFileFixture, Actual_Write_RESULT_Success)
{

}

TEST_F(MockFileFixture, Actual_Write_RESULT_Fail)
{

}

TEST_F(MockFileFixture, LBA0_Read_Data_Success)
{
	EXPECT_CALL(mFile, readFromNANDTxt)
		.Times(100);
	EXPECT_CALL(mFile, writeToResultTxt(0, _))
		.Times(1);

	ssd->read(0);
}

TEST_F(MockFileFixture, LBA100_Read_Fail)
{
	EXPECT_CALL(mFile, readFromNANDTxt(0))
		.Times(0);
	EXPECT_CALL(mFile, writeToResultTxt(0, "0x12345678"))
		.Times(0);

	ssd->read(100);
}

TEST_F(MockFileFixture, LBA0_Write_Data_0x1234_5678_Success)
{
	EXPECT_CALL(mFile, readFromNANDTxt)
		.Times(100);
	EXPECT_CALL(mFile, writeToNANDTxt)
		.Times(100);

	ssd->write(0, "0x12345678");
}

TEST_F(MockFileFixture, LBA100_Write_Fail)
{
	EXPECT_CALL(mFile, readFromNANDTxt)
		.Times(0);
	EXPECT_CALL(mFile, writeToNANDTxt)
		.Times(0);

	ssd->write(100, "0x12345678");
}

TEST_F(MockFileFixture, LBA0_Write_Data_0x0000_0000_0000_Fail)
{
	EXPECT_CALL(mFile, readFromNANDTxt)
		.Times(0);
	EXPECT_CALL(mFile, writeToNANDTxt)
		.Times(0);

	ssd->write(0, "0x000000000000");
}