#pragma once

#include "CommandHandler.cpp"

#include <iostream>

using namespace std;

class Write : public CommandHandler
{
public:
	Write(ostream& _out, SsdHelper& _ssd) : CommandHandler(_out, _ssd) {};

	bool isValidArgs(const vector<string>& args) override
	{
		if (isInvalidNumberOfArguments(args)) return INVALID;
		if (isLbaOutOfRange(args[1])) return INVALID;
		if (isInvalidLengthOfData(args[2])) return INVALID;
		if (isInvalidPrefix(args[2])) return INVALID;
		if (hasInvalidCharater(args[2])) return INVALID;

		return VALID;
	}

	Progress doCommand(const vector<string>& args) override
	{
		logger.print("Command : " + sliceString(args, 0));
		string arguments = "W " + args[1] + " " + args[2];
		m_ssdHelper.execute(arguments);
		return Progress::Continue;
	}

	void usage() override {};

	~Write() {};
private:

    bool isInvalidLengthOfData(const std::string& data)
    {
        if (data.size() != 10)
        {
            m_outputStream << "[WARNING] Invalid input data length !!!" << endl;
			return true;
        }
        return false;
    }

    bool isInvalidPrefix(const std::string& inputData)
    {
        if (inputData[0] != '0' || inputData[1] != 'x')
        {
            m_outputStream << "[WARNING] Prefix '0x' was not included in input data !!!" << endl;
            return true;
        }
        return false;
    }

    bool hasInvalidCharater(const std::string& inputData)
    {
        for (int index = 2; index < inputData.length(); index++)
        {
            if (('A' <= inputData[index] && inputData[index] <= 'F') || ('0' <= inputData[index] && inputData[index] <= '9'))
            {
                continue;
            }

            m_outputStream << "[WARNING] Input data has invalid characters !!!" << endl;
            return true;
        }

        return false;
    }

	bool isInvalidNumberOfArguments(const std::vector<std::string>& args)
	{
		return (args.size() != 3);
	}

	bool isLbaOutOfRange(const string& lbaString)
	{
		return stoi(lbaString) < 0 || stoi(lbaString) > 99;
	}
};