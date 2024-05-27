#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../Shell/SsdExcutable.h"
#include "../Shell/SsdResult.h"

class SsdExcutalbeMock : public ISsdExecutable
{
public:
    MOCK_METHOD(bool, execute, (const string&), (override));
private:
};

class SsdResultMock : public ISsdResult
{
public:
    MOCK_METHOD(string, get, (), (override));
};
