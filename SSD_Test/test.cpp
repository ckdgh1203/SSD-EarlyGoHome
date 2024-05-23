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

class WriteMockFileFixture : public testing::Test
{
public:
	void SetUp() override
	{
		ssd = new SSD(&wCmd);
	}
	WriteCommand wCmd{&mFile, 0,"0x00000000" };
	NiceMock<MockFile> mFile;
	SSD* ssd;
};

class ReadMockFileFixture : public testing::Test
{
public:
	void SetUp() override
	{
		ssd = new SSD(&rCmd);
	}
	ReadCommand rCmd{ &mFile, 0};
	NiceMock<MockFile> mFile;
	SSD* ssd;
};

TEST_F(ReadMockFileFixture, LBA0_Read_Data_Success)
{
	EXPECT_CALL(mFile, readFromNANDTxt)
		.Times(100);
	EXPECT_CALL(mFile, writeToResultTxt(0, _))
		.Times(1);
	ssd->executeCommand();
}

TEST_F(ReadMockFileFixture, LBA100_Read_Fail)
{
	EXPECT_CALL(mFile, readFromNANDTxt(0))
		.Times(0);
	EXPECT_CALL(mFile, writeToResultTxt(0, "0x12345678"))
		.Times(0);
	ReadCommand rCmd{ &mFile, 100};
	ssd->setCommand(&rCmd);
	ssd->executeCommand();
}

TEST_F(WriteMockFileFixture, LBA0_Write_Data_0x1234_5678_Success)
{
	EXPECT_CALL(mFile, readFromNANDTxt)
		.Times(100);
	EXPECT_CALL(mFile, writeToNANDTxt)
		.Times(100);
	WriteCommand wCmd{ &mFile, 0, "0x12345678" };
	ssd->setCommand(&wCmd);
	ssd->executeCommand();
}

TEST_F(WriteMockFileFixture, LBA100_Write_Fail)
{
	EXPECT_CALL(mFile, readFromNANDTxt)
		.Times(0);
	EXPECT_CALL(mFile, writeToNANDTxt)
		.Times(0);
	WriteCommand wCmd{ &mFile, 100, "0x12345678" };
	ssd->setCommand(&wCmd);
	ssd->executeCommand();
}

TEST_F(WriteMockFileFixture, LBA0_Write_Data_0x0000_0000_0000_Fail)
{
	EXPECT_CALL(mFile, readFromNANDTxt)
		.Times(0);
	EXPECT_CALL(mFile, writeToNANDTxt)
		.Times(0);
	WriteCommand wCmd{ &mFile, 100, "0x000000000000" };
	ssd->setCommand(&wCmd);
	ssd->executeCommand();
}

TEST(SSD_Test, CommandExecute_Write)
{
	NiceMock<MockFile> mFile;
	WriteCommand wCmd{&mFile, 0, "0x00000000"};
	SSD ssd{&wCmd};

	ssd.executeCommand();

}

TEST(SSD_Test, CommandExecute_Read)
{
	NiceMock<MockFile> mFile;
	ReadCommand rCmd{&mFile, 0};
	SSD ssd{&rCmd };

	ssd.executeCommand();

}

TEST(SSD_Test, CommandExecute_ChangeCommand)
{
	NiceMock<MockFile> mFile;
	ReadCommand rCmd{ &mFile, 0 };
	SSD ssd{&rCmd };
	WriteCommand wCmd{ &mFile, 0, "0x00000000" };
	ssd.setCommand(&wCmd);
	ssd.executeCommand();
}
