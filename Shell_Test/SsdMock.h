#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../Shell/SsdExcutable.h"
#include "../Shell/SsdResult.h"

class SsdExcutalbeMock : public ISsdExecutable
{
public:
    MOCK_METHOD(bool, execute, (const string&), (override));
    MOCK_METHOD(string, getResultFilePath, (), (override));
private:
};

class SsdResultMock : public ISsdResult
{
public:
    MOCK_METHOD(string, get, (), (override));
    MOCK_METHOD(void, setResultFilePath, (string), (override));
};
