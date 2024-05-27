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
	MOCK_METHOD(vector<string>, readFromNANDTxt, (int), (override));
	MOCK_METHOD(void, writeToNANDTxt, (vector<string> buf), (override));
	MOCK_METHOD(string, readFromResultTxt, (), (override));
	MOCK_METHOD(void, writeToResultTxt, (string), (override));
};

class WriteMockFileFixture : public testing::Test
{
public:
	void SetUp() override
	{
		ssd = new SSD(&wCmd);
	}
	WriteCommand wCmd{ &mFile, 0,"0x00000000" };
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
	ReadCommand rCmd{ &mFile, 0 };
	NiceMock<MockFile> mFile;
	SSD* ssd;
};

class FileTestFixture : public testing::Test
{
public:
	void SetUp() override
	{
		sFile.initTxtFiles();
	}

	void TearDown() override
	{
		for (int i = 0; i < FILE_TEST_NUM; i++)
		{
			ValidateFileTest(expected[i], actual[i]);
		}
	}

	void ValidateFileTest(const string expectedValue, const string actualValue)
	{
		EXPECT_EQ(expectedValue, actualValue);
	}

	string filePath = "../Data/";
	SSDFile sFile{ filePath };
	
protected:
	string expected[FILE_TEST_NUM];
	string actual[FILE_TEST_NUM];
};


TEST_F(ReadMockFileFixture, LBA0_Read_Data_Success)
{
	EXPECT_CALL(mFile, readFromNANDTxt)
		.Times(100);
	EXPECT_CALL(mFile, writeToResultTxt)
		.Times(1);
	ssd->executeCommand();
}

TEST_F(ReadMockFileFixture, DISABLED_LBA100_Read_Fail)
{
	EXPECT_CALL(mFile, readFromNANDTxt)
		.Times(0);
	EXPECT_CALL(mFile, writeToResultTxt)
		.Times(0);
	ReadCommand rCmd{ &mFile, 100 };
	ssd->setCommand(&rCmd);
	ssd->executeCommand();
}

TEST_F(WriteMockFileFixture, DISABLED_LBA0_Write_Data_0x1234_5678_Success)
{
	EXPECT_CALL(mFile, readFromNANDTxt)
		.Times(100);
	EXPECT_CALL(mFile, writeToNANDTxt)
		.Times(1);
	WriteCommand wCmd{ &mFile, 0, "0x12345678" };
	ssd->setCommand(&wCmd);
	ssd->executeCommand();
}

TEST_F(WriteMockFileFixture, DISABLED_LBA100_Write_Fail)
{
	EXPECT_CALL(mFile, readFromNANDTxt)
		.Times(0);
	EXPECT_CALL(mFile, writeToNANDTxt)
		.Times(0);
	WriteCommand wCmd{ &mFile, 100, "0x12345678" };
	ssd->setCommand(&wCmd);
	ssd->executeCommand();
}

TEST_F(WriteMockFileFixture, DISABLED_LBA0_Write_Data_0x0000_0000_0000_Fail)
{
	EXPECT_CALL(mFile, readFromNANDTxt)
		.Times(0);
	EXPECT_CALL(mFile, writeToNANDTxt)
		.Times(0);
	WriteCommand wCmd{ &mFile, 100, "0x000000000000" };
	ssd->setCommand(&wCmd);
	ssd->executeCommand();
}

TEST_F(WriteMockFileFixture, DISABLED_CommandExecute_Write)
{
	EXPECT_CALL(mFile, readFromNANDTxt)
		.Times(100);
	EXPECT_CALL(mFile, writeToNANDTxt)
		.Times(1);

	ssd->executeCommand();
}

TEST_F(ReadMockFileFixture, DISABLED_CommandExecute_Read)
{
	EXPECT_CALL(mFile, readFromNANDTxt)
		.Times(100);
	EXPECT_CALL(mFile, writeToResultTxt(_))
		.Times(1);

	ssd->executeCommand();
}

TEST_F(ReadMockFileFixture, DISABLED_CommandExecute_ChangeCommand)
{
	EXPECT_CALL(mFile, readFromNANDTxt)
		.Times(100);
	EXPECT_CALL(mFile, writeToNANDTxt)
		.Times(1);
	EXPECT_CALL(mFile, writeToResultTxt(_))
		.Times(0);

	WriteCommand wCmd{ &mFile, 0, "0x00000000" };

	ssd->setCommand(&wCmd);
	ssd->executeCommand();
}

TEST_F(WriteMockFileFixture, DISABLED_CommandFactory_CreateWriteCommand)
{
	EXPECT_CALL(mFile, readFromNANDTxt)
		.Times(100);
	EXPECT_CALL(mFile, writeToNANDTxt)
		.Times(1);
	CommandFactory& cf = CommandFactory::getInstance();
	Command* cmd = cf.createCommand(&mFile, 0, "0x12345678");

	ssd->setCommand(cmd);
	ssd->executeCommand();
}

TEST_F(ReadMockFileFixture, DISABLED_CommandFactory_CreateReadCommand)
{
	EXPECT_CALL(mFile, readFromNANDTxt)
		.Times(100);
	EXPECT_CALL(mFile, writeToResultTxt(_))
		.Times(1);

	CommandFactory& cf = CommandFactory::getInstance();
	Command* cmd = cf.createCommand(&mFile, 0);

	ssd->setCommand(cmd);
	ssd->executeCommand();
}

TEST_F(FileTestFixture, Actual_Read_NAND_Success)
{
	expected[99] = DEFAULT_DATA;
	vector<string> temp = sFile.readFromNANDTxt(0);
	actual[99] = temp[99];
}

TEST_F(FileTestFixture, Actual_Read_RESULT_Success)
{
	expected[0] = DEFAULT_DATA;
	actual[0] = sFile.readFromResultTxt();
}

TEST_F(FileTestFixture, Actual_Write_NAND_Success)
{
	vector<string> buf;
	for (int i = 0; i < 100; i++)
	{
		buf.push_back("0x00000001");
	}
	sFile.writeToNANDTxt(buf);

	expected[99] = "0x00000001";
	vector<string> temp = sFile.readFromNANDTxt(0);
	actual[99] = temp[99];
}

TEST_F(FileTestFixture, Actual_Write_RESULT_Success)
{
	sFile.writeToResultTxt("0x00000001");

	expected[0] = "0x00000001";
	actual[0] = sFile.readFromResultTxt();
}